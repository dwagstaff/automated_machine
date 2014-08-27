/**
 * 
 */
package com.wagstaffnet.tivo.app;

import java.io.IOException;
import java.io.InputStream;
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
import javax.xml.bind.JAXBContext;
import javax.xml.bind.JAXBException;
import javax.xml.bind.Unmarshaller;

import org.apache.http.auth.AuthScope;
import org.apache.http.auth.UsernamePasswordCredentials;
import org.apache.http.client.CredentialsProvider;
import org.apache.http.client.methods.CloseableHttpResponse;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.conn.ssl.SSLConnectionSocketFactory;
import org.apache.http.conn.ssl.SSLContexts;
import org.apache.http.conn.ssl.TrustStrategy;
import org.apache.http.impl.client.BasicCredentialsProvider;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.HttpClients;

import com.wagstaffnet.tivo.masterlist.TiVoContainer;

/**
 * @author davew
 *
 */
public class TivoAppAdaptor {
	private static Logger log= Logger.getLogger(TivoAppAdaptor.class.getCanonicalName());

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
	public static void main(String[] args) throws JAXBException, IOException, KeyManagementException, NoSuchAlgorithmException, KeyStoreException {
		log.info("Starting Operation");
		
		// First open the sample file
		InputStream inps= TivoAppAdaptor.class.getResourceAsStream("TivoMasterList.xml");
		System.out.println("inps= " + inps.toString());

		parseTivoMasterList(inps);
		
		// Get Items, 50 at a time
		List<TiVoContainer.Item> shows= new ArrayList<TiVoContainer.Item>();
		{
			int startItem= 0;
			List<TiVoContainer.Item> items;
			do {
				items= getTivoDetails(startItem, 50);
				shows.addAll(items);
				startItem+= items.size();
			} while(items.size() > 0 );
		}
		System.out.printf("Total shows loaded: %d\n", shows.size());
	}

	private static TiVoContainer parseTivoMasterList(InputStream inps)
			throws JAXBException {
		JAXBContext jc= JAXBContext.newInstance(TiVoContainer.class);
		Unmarshaller unmarshaller= jc.createUnmarshaller();
		
		TiVoContainer tiVoContainer= (TiVoContainer) unmarshaller.unmarshal(inps);
		if( tiVoContainer == null )
			System.out.println("Unable to parse xml");
		else
			System.out.println(tiVoContainer.getItemCount());
		return tiVoContainer;
	}
	
	public static List<TiVoContainer.Item> getTivoDetails(int itemStart, int itemCount) throws IOException, KeyManagementException, NoSuchAlgorithmException, KeyStoreException, IllegalStateException, JAXBException {
		TiVoContainer container= null;
		
		System.out.printf("Loading items %d - %d\n", itemStart, itemStart+itemCount);
		
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

            System.out.println("Executing request " + httpget.getRequestLine());
            CloseableHttpResponse response = httpclient.execute(httpget);
            try {
                System.out.println("----------------------------------------");
                System.out.println(response.getStatusLine());
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
	
	private static SSLContext buildSSLContext()
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
