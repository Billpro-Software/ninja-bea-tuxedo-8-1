item_1 = "Learn about JDeveloper's new features, take a tour, and get started developing your first application.";
item_2 = "Create and use web services, and configure connections to use with them.";
item_3 = "Build web or Java client applications using Oracle ADF, JSF, EJB, and Swing technologies.";
item_4 = "Design, create and browse database objects, including PL/SQL.";
item_5 = "Create class, activity, sequence, use case, EJB and database diagrams.";

var myPar = location.href.split('?');
var divideAgain = myPar[1].split('&');
var divideAgainAgain = divideAgain[0].split('=');
var webCenter = divideAgainAgain[1];

divideAgainAgain = divideAgain[1].split('=');
var soa = divideAgainAgain[1];

function gotoLink(par){
	//alert(webCenter + ' ' + soa);
	var linkAddress = par + "?oracle.webcenter.framework=" + webCenter + "&oracle.sca.modeler=" + soa; 
	//alert(linkAddress);
	window.location = linkAddress;
}

function showDescription(id)
{
	var num = id.charAt(4);
	var selectedMenu = "menu_item_" + num;
	var selectedLinkLeft = "link_" + num + "_left";
	var selectedLinkCenter = "link_" + num + "_center";
	var selectedLinkRight = "link_" + num + "_right";
	
	document.getElementById("description_box").innerHTML = eval("item_"+ num);
	//document.getElementById(selectedMenu).style.background = "url(welcomeImages/mouse_over_left.png)";
	
	document.getElementById(selectedLinkLeft).className = 'link_text_over_left';
	document.getElementById(selectedLinkCenter).className = 'link_text_over_center';
	document.getElementById(selectedLinkRight).className = 'link_text_over_right';
}

function mouseOut(id)
{
	var num = id.charAt(4);
	var selectedMenu = "menu_item_" + num;
	var selectedLinkLeft = "link_" + num + "_left";
	var selectedLinkCenter = "link_" + num + "_center";
	var selectedLinkRight = "link_" + num + "_right";
	
	document.getElementById("description_box").innerHTML = "";
	//document.getElementById(selectedMenu).style.background = "url(welcomeImages/default_2.png)";
	document.getElementById(selectedLinkLeft).className = 'link_text_left';
	document.getElementById(selectedLinkCenter).className = 'link_text_center';
	document.getElementById(selectedLinkRight).className = 'link_text_right';
}

function clickMenu(id)
{
	var num = id.charAt(4);
	var selectedMenu = "menu_item_" + num;
	var selectedLinkLeft = "link_" + num + "_left";
	var selectedLinkCenter = "link_" + num + "_center";
	var selectedLinkRight = "link_" + num + "_right";
	
	//document.getElementById(selectedMenu).style.background = "url(welcomeImages/mouseDown_2.png)";
	document.getElementById(selectedLinkLeft).className = 'link_text_down_left';
	document.getElementById(selectedLinkCenter).className = 'link_text_down_center';
	document.getElementById(selectedLinkRight).className = 'link_text_down_right';
}

function detectBrowser()
{
	var browser=BrowserDetect.browser;
	var b_version=BrowserDetect.version;
	var version=parseFloat(b_version);
	if ((browser=="Microsoft Internet Explorer") && (version<=6))
	 {
		alert("This page only runs on Internet Explorer 7, Firefox 2.0.0.1, or ICEBrowser SDK. Thank you!");
		window.location = "http://www.microsoft.com/windows/products/winfamily/ie/default.mspx";
		
	}
}


var BrowserDetect = {
	init: function () {
		this.browser = this.searchString(this.dataBrowser) || "An unknown browser";
		this.version = this.searchVersion(navigator.userAgent)
			|| this.searchVersion(navigator.appVersion)
			|| "an unknown version";
		this.OS = this.searchString(this.dataOS) || "an unknown OS";
	},
	searchString: function (data) {
		for (var i=0;i<data.length;i++)	{
			var dataString = data[i].string;
			var dataProp = data[i].prop;
			this.versionSearchString = data[i].versionSearch || data[i].identity;
			if (dataString) {
				if (dataString.indexOf(data[i].subString) != -1)
					return data[i].identity;
			}
			else if (dataProp)
				return data[i].identity;
		}
	},
	searchVersion: function (dataString) {
		var index = dataString.indexOf(this.versionSearchString);
		if (index == -1) return;
		return parseFloat(dataString.substring(index+this.versionSearchString.length+1));
	},
	dataBrowser: [
		{ 	string: navigator.userAgent,
			subString: "OmniWeb",
			versionSearch: "OmniWeb/",
			identity: "OmniWeb"
		},
		{
			string: navigator.vendor,
			subString: "Apple",
			identity: "Safari"
		},
		{
			prop: window.opera,
			identity: "Opera"
		},
		{
			string: navigator.vendor,
			subString: "iCab",
			identity: "iCab"
		},
		{
			string: navigator.vendor,
			subString: "KDE",
			identity: "Konqueror"
		},
		{
			string: navigator.userAgent,
			subString: "Firefox",
			identity: "Firefox"
		},
		{
			string: navigator.vendor,
			subString: "Camino",
			identity: "Camino"
		},
		{		// for newer Netscapes (6+)
			string: navigator.userAgent,
			subString: "Netscape",
			identity: "Netscape"
		},
		{
			string: navigator.userAgent,
			subString: "MSIE",
			identity: "Explorer",
			versionSearch: "MSIE"
		},
		{
			string: navigator.userAgent,
			subString: "Gecko",
			identity: "Mozilla",
			versionSearch: "rv"
		},
		{ 		// for older Netscapes (4-)
			string: navigator.userAgent,
			subString: "Mozilla",
			identity: "Netscape",
			versionSearch: "Mozilla"
		}
	],
	dataOS : [
		{
			string: navigator.platform,
			subString: "Win",
			identity: "Windows"
		},
		{
			string: navigator.platform,
			subString: "Mac",
			identity: "Mac"
		},
		{
			string: navigator.platform,
			subString: "Linux",
			identity: "Linux"
		}
	]

};
BrowserDetect.init();

