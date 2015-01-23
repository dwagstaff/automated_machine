package com.wagstaffnet.tivo.app.model;

import java.io.StringWriter;

import javax.persistence.Column;
import javax.persistence.Embedded;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.xml.bind.JAXBContext;
import javax.xml.bind.JAXBException;
import javax.xml.bind.Marshaller;

import com.wagstaffnet.tivo.masterlist.TiVoContainer;

@Entity
public class ShowInfo  {
	@Id
	private String id;

	@Embedded
	private TiVoContainer.Item itemInfo;
	private String itemDetail;
	
	/**
	 * @return the id
	 */
	public String getId() {
		return id;
	}
	/**
	 * @param id the id to set
	 */
	public void setId(String id) {
		this.id = id;
	}
	/**
	 * @return the itemInfo
	 */
	public TiVoContainer.Item getItemInfo() {
		return itemInfo;
	}
	/**
	 * @param itemInfo the itemInfo to set
	 */
	public void setItemInfo(TiVoContainer.Item itemInfo) {
		this.itemInfo = itemInfo;
	}
	/**
	 * @return the itemDetail
	 */
	public TvBusEnvelope getItemDetail() {
		return null;
	}
	/**
	 * @param itemDetail the itemDetail to set
	 * @throws JAXBException 
	 */
	public void setItemDetail(TvBusEnvelope itemDetail) throws JAXBException {
		JAXBContext jc= JAXBContext.newInstance(TvBusEnvelope.class);
		Marshaller mash= jc.createMarshaller();
		StringWriter swrt= new StringWriter();
		mash.marshal(itemDetail, swrt);
		this.itemDetail= swrt.toString();
	}
}
