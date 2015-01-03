/**
 * 
 */
package com.wagstaffnet.tivo.app;

import com.wagstaffnet.tivo.app.model.ShowInfo;
import com.wagstaffnet.tivo.app.model.TvBusEnvelope;
import com.wagstaffnet.tivo.masterlist.TiVoContainer;
import com.wagstaffnet.tivo.masterlist.TiVoContainer.Item.Links.TiVoVideoDetails;

import org.apache.http.auth.AuthScope;
import org.apache.http.auth.UsernamePasswordCredentials;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.CredentialsProvider;
import org.apache.http.client.methods.CloseableHttpResponse;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.conn.ssl.SSLConnectionSocketFactory;
import org.apache.http.conn.ssl.SSLContexts;
import org.apache.http.conn.ssl.TrustStrategy;
import org.apache.http.impl.client.BasicCredentialsProvider;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.HttpClients;

import java.io.IOException;
import java.io.InputStream;
import java.io.StringWriter;
import java.security.KeyManagementException;
import java.security.KeyStoreException;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.security.cert.CertificateException;
import java.security.cert.X509Certificate;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Logger;

import javax.net.ssl.SSLContext;
import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.Persistence;
import javax.xml.bind.JAXBContext;
import javax.xml.bind.JAXBException;
import javax.xml.bind.Marshaller;
import javax.xml.bind.Unmarshaller;

/**
 * @author davew
 *
 */
public class TivoAppAdaptor {

	/***
	 * The number of show descriptors to download per request.
	 * The system will continue to send request with increasing starting
	 * points at this value number of items per request until all of the items
	 * have been retrieved.
	 */
	private static final int SHOW_CHUNK_SIZE = 50;
	private static Logger log= Logger.getLogger(TivoAppAdaptor.class.getCanonicalName());
	private EntityManagerFactory emf;
	private EntityManager em;

	/**
	 * 
	 */
	public TivoAppAdaptor() {
		// TODO Auto-generated constructor stub
	}

	/**
	 * @param args
	 * @throws JAXBException 
	 * @throws IOException 
	 * @throws KeyStoreException 
	 * @throws NoSuchAlgorithmException 
	 * @throws KeyManagementException 
	 */
	public static void main(String[] args) {
		TivoAppAdaptor app= new TivoAppAdaptor();
		app.runLoop();
	}

	/**
	 * 
	 */
	public void runLoop() {
		try {
			log.info("Starting Operation");
			
			log.info("Connecting to DB");
//			emf = Persistence.createEntityManagerFactory( "jpa" );
			emf = Persistence.createEntityManagerFactory( "mongo" );
	        em = emf.createEntityManager();
       
			// First open the sample file
			InputStream inps= TivoAppAdaptor.class.getResourceAsStream("TivoMasterList.xml");
			System.out.println("inps= " + inps.toString());

			parseTivoMasterList(inps);
			
			// Get Items, SHOW_CHUNK_SIZE at a time
			log.info("Starting Tivo read ...");
			List<TiVoContainer.Item> shows= new ArrayList<TiVoContainer.Item>();
			{
				int startItem= 0;
				List<TiVoContainer.Item> items;
				do {
					items= getTivoDetails(startItem, SHOW_CHUNK_SIZE);
					shows.addAll(items);
					startItem+= items.size();
				} while(items.size() > 0 );
				log.info(String.format("Total shows loaded: %d\n", shows.size()));

				// Save the data to the database
				int i= 0;
				int newShows= 0;
				int presentShows= 0;
				for(TiVoContainer.Item item : shows) {
					// Start Transaction
					em.getTransaction().begin();
					
					// See if we have a know about this already
					ShowInfo showFound= em.find(ShowInfo.class, item.getLinks().getContent().getUrl());
					if(  showFound ==  null ) {
						em.getTransaction().begin();
						newShows++;
						ShowInfo show= new ShowInfo();
						show.setId(item.getLinks().getContent().getUrl());
						show.setItemInfo(item);

						// Add show info						
						{
							log.info("Getting show information");
							TvBusEnvelope detail= getVideoDetail(item.getLinks().getTiVoVideoDetails().getUrl());
							show.setItemDetail(detail);
//							JAXBContext jc= JAXBContext.newInstance(TvBusEnvelope.class);
//							Marshaller mash= jc.createMarshaller();
//							StringWriter swrt= new StringWriter();
//							mash.marshal(detail, swrt);
//							show.setXmlInfo(swrt.toString());
//							swrt.close();
//							em.getTransaction().begin();
//							em.persist(show);
//							em.getTransaction().commit();
						}

//						item.setId(item.getId());
	//					item.id= item.getLinks().getContent().getUrl();
//						em.persist(item.getDetails());
//						em.persist(item.getLinks());
//						em.persist(item.getLinks().getContent());
//						em.persist(item.getLinks().getTiVoVideoDetails());
//						if( item.getLinks().getCustomIcon() != null )
//							em.persist(item.getLinks().getCustomIcon());
						log.info("Saving data");
						em.persist(show);
						log.info("Saved item " + (i++) + " of " + shows.size());
					} else {
						showFound.getItemInfo().getDetails().setInProgress(item.getDetails().getInProgress());
						presentShows++;
						log.info("Item skipped " + i++);
					}
	 				em.getTransaction().commit();
				}
				log.info("DB save completed");
				log.info("New Shows: " + newShows);
				log.info("Existing: " + presentShows);
			}
		} catch (KeyManagementException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (NoSuchAlgorithmException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (KeyStoreException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalStateException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (JAXBException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		em.close();
		emf.close();
	}

	private  TiVoContainer parseTivoMasterList(InputStream inps)
			throws JAXBException {
		JAXBContext jc= JAXBContext.newInstance(TiVoContainer.class);
		Unmarshaller unmarshaller= jc.createUnmarshaller();
		
		TiVoContainer tiVoContainer= (TiVoContainer) unmarshaller.unmarshal(inps);
		if( tiVoContainer == null )
			System.out.println("Unable to parse xml");
		return tiVoContainer;
	}

	private  TvBusEnvelope parseTivoVideoDetail(InputStream inps)
			throws JAXBException {
		JAXBContext jc= JAXBContext.newInstance(TvBusEnvelope.class);
		Unmarshaller unmarshaller= jc.createUnmarshaller();
		
		TvBusEnvelope tiVoVideoDetail= (TvBusEnvelope) unmarshaller.unmarshal(inps);
		if( tiVoVideoDetail == null )
			System.out.println("Unable to parse xml");
		return tiVoVideoDetail;
	}

	public  List<TiVoContainer.Item> getTivoDetails(int itemStart, int itemCount) throws IOException, KeyManagementException, NoSuchAlgorithmException, KeyStoreException, IllegalStateException, JAXBException {
		TiVoContainer container= null;
		log.info(String.format("Loading items %d - %d\n", itemStart, itemStart+itemCount));
		
		// Generate the URL that we are going to be using
		String urlText= String.format("https://wagstaffgw.dyndns.org:4443/TiVoConnect?Command=QueryContainer&Container=/NowPlaying&Recurse=Yes&AnchorOffset=%d&ItemCount=%d", itemStart, itemCount);
		
		// Trust all certs
		   // Trust all certs
	    SSLContext sslcontext = buildSSLContext();

	    // Allow TLSv1 protocol only
	    SSLConnectionSocketFactory sslsf = new SSLConnectionSocketFactory(
	            sslcontext,
	            new String[] { "TLSv1" },
	            null,
	            SSLConnectionSocketFactory.ALLOW_ALL_HOSTNAME_VERIFIER);

        CredentialsProvider credsProvider = new BasicCredentialsProvider();
        credsProvider.setCredentials(
                new AuthScope("wagstaffgw.dyndns.org", 4443),
                new UsernamePasswordCredentials("tivo", "6641492404"));
        CloseableHttpClient httpclient = HttpClients.custom()
                .setDefaultCredentialsProvider(credsProvider)
//                .setHostnameVerifier(new AllowAllHostnameVerifier())
                .setSSLSocketFactory(sslsf)
                .build();
        try {
            HttpGet httpget = new HttpGet(urlText);

            log.fine("Executing request " + httpget.getRequestLine());
            CloseableHttpResponse response = httpclient.execute(httpget);
            try {
                log.fine("----------------------------------------");
                log.fine("HTTP Status: " + response.getStatusLine());
                container= parseTivoMasterList(response.getEntity().getContent());
                //EntityUtils.consume(response.getEntity());
            } finally {
                response.close();
            }
        } finally {
            httpclient.close();
        }
	
        if( container != null )
        	return container.getItem();
        else
        	return null;
	}

	private TvBusEnvelope getVideoDetail(String url) throws KeyManagementException, NoSuchAlgorithmException, KeyStoreException, ClientProtocolException, IOException, IllegalStateException, JAXBException {
		TvBusEnvelope details;

		
		// Generate the URL that we are going to be using
		String urlText= url.replace(":443/", ":4443/");
		
		// Trust all certs
		   // Trust all certs
	    SSLContext sslcontext = buildSSLContext();

	    // Allow TLSv1 protocol only
	    SSLConnectionSocketFactory sslsf = new SSLConnectionSocketFactory(
	            sslcontext,
	            new String[] { "TLSv1" },
	            null,
	            SSLConnectionSocketFactory.ALLOW_ALL_HOSTNAME_VERIFIER);

        CredentialsProvider credsProvider = new BasicCredentialsProvider();
        credsProvider.setCredentials(
                new AuthScope("wagstaffgw.dyndns.org", 4443),
                new UsernamePasswordCredentials("tivo", "6641492404"));
        CloseableHttpClient httpclient = HttpClients.custom()
                .setDefaultCredentialsProvider(credsProvider)
//                .setHostnameVerifier(new AllowAllHostnameVerifier())
                .setSSLSocketFactory(sslsf)
                .build();
        try {
            HttpGet httpget = new HttpGet(urlText);

            log.fine("Executing request " + httpget.getRequestLine());
            CloseableHttpResponse response = httpclient.execute(httpget);
            try {
                log.fine("----------------------------------------");
                log.fine("HTTP Status: " + response.getStatusLine());
                details= parseTivoVideoDetail(response.getEntity().getContent());
                //EntityUtils.consume(response.getEntity());
            } finally {
                response.close();
            }
        } finally {
            httpclient.close();
        }
        return details;
	}
	
	private  SSLContext buildSSLContext()
	        throws NoSuchAlgorithmException, KeyManagementException,
	        KeyStoreException {
	    SSLContext sslcontext = SSLContexts.custom()
	            .setSecureRandom(new SecureRandom())
	            .loadTrustMaterial(null, new TrustStrategy() {

	                public boolean isTrusted(X509Certificate[] chain, String authType)
	                        throws CertificateException {
	                    return true;
	                }
	            })
	            .build();
	    return sslcontext;
	}
}
