package com.wagstaffnet.tivo.app.model;

import com.wagstaffnet.tivo.masterlist.TiVoContainer;

public class Show extends TiVoContainer.Item {

	public String getID() {
		return String.format("", getDetails().getTitle(), getDetails().getShowingStartTime() );
	}
}
