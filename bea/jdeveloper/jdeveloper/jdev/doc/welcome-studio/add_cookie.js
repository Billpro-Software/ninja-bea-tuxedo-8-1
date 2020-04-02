var more_showing = true;
var flag = 'few';
var first_time = 'false';

var myPar = location.href.split('?');
var divideAgain = myPar[1].split('&');
var divideAgainAgain = divideAgain[0].split('=');
var webCenter = divideAgainAgain[1];

divideAgainAgain = divideAgain[1].split('=');
var soa = divideAgainAgain[1];

function loadMe() {
	
	if(webCenter == 1 && soa == 1){
		document.getElementById('yes_soa').style.display = "none";
		document.getElementById('yes_webcenter').style.display = "none";
		document.getElementById('yes_websoa').style.display = "block";
		document.getElementById('no_websoa').style.display = "none";
	}
	else if (webCenter == 1 && soa == 0) {
		document.getElementById('yes_soa').style.display = "none";
		document.getElementById('yes_webcenter').style.display = "block";
		document.getElementById('yes_websoa').style.display = "none";
		document.getElementById('no_websoa').style.display = "none";
	}
	else if (webCenter == 0 && soa == 1) {
		document.getElementById('yes_soa').style.display = "block";
		document.getElementById('yes_webcenter').style.display = "none";
		document.getElementById('yes_websoa').style.display = "none";
		document.getElementById('no_websoa').style.display = "none";
	}
	else if (webCenter == 0 && soa == 0) { 
		document.getElementById('yes_soa').style.display = "none";
		document.getElementById('yes_webcenter').style.display = "none";
		document.getElementById('yes_websoa').style.display = "none";
		document.getElementById('no_websoa').style.display = "block";
	}
}

function hideAndShow() {
	alert(username);
	if(more_showing && username == 'more'){
		
		alert("Showing Less right now");
		document.getElementById('switch_text').innerHTML = 'Show More >';
		
		show_few();
		more_showing = false;
		username='few';
		setCookie('username',username,365);
		username=getCookie('username');
		
		alert("username;:::::" + username);
		
	}
	else {
		
		alert("Going to show more");
		document.getElementById('switch_text').innerHTML = 'Show Fewer >';
		
		show_more();
		more_showing = true;
		username='more';
		setCookie('username',username,365);
		getCookie('username');
		
		alert("username;:::::>>>>" + username);
		//alert(flag);
	}
}
function show_few() {
	alert('I am in show_few function');
	alert(webCenter + ' ' + soa);
	if(webCenter == 1 && soa == 1){
		document.getElementById('soa_show_few').style.display = "none";
		document.getElementById('soa_show_more').style.display = "none";
		document.getElementById('webcenter_show_few').style.display = "none";
		document.getElementById('webcenter_show_more').style.display = "none";
		document.getElementById('none_show_few').style.display = "none";
		document.getElementById('none_show_more').style.display = "none";
		document.getElementById('websoa_show_few').style.display = "block";
		document.getElementById('websoa_show_more').style.display = "none";
	}
	else if (webCenter == 1 && soa == 0) {
		document.getElementById('soa_show_few').style.display = "none";
		document.getElementById('soa_show_more').style.display = "none";
		document.getElementById('webcenter_show_few').style.display = "block";
		document.getElementById('webcenter_show_more').style.display = "none";
		document.getElementById('none_show_few').style.display = "none";
		document.getElementById('none_show_more').style.display = "none";
		document.getElementById('websoa_show_few').style.display = "none";
		document.getElementById('websoa_show_more').style.display = "none";
	}
	else if (webCenter == 0 && soa == 1) {
		document.getElementById('soa_show_few').style.display = "block";
		document.getElementById('soa_show_more').style.display = "none";
		document.getElementById('webcenter_show_few').style.display = "none";
		document.getElementById('webcenter_show_more').style.display = "none";
		document.getElementById('none_show_few').style.display = "none";
		document.getElementById('none_show_more').style.display = "none";
		document.getElementById('websoa_show_few').style.display = "none";
		document.getElementById('websoa_show_more').style.display = "none";
	}
	else if (webCenter == 0 && soa == 0) { 
		document.getElementById('soa_show_few').style.display = "none";
		document.getElementById('soa_show_more').style.display = "none";
		document.getElementById('webcenter_show_few').style.display = "none";
		document.getElementById('webcenter_show_more').style.display = "none";
		document.getElementById('none_show_few').style.display = "block";
		document.getElementById('none_show_more').style.display = "none";
		document.getElementById('websoa_show_few').style.display = "none";
		document.getElementById('websoa_show_more').style.display = "none";
	}		
}

function show_more() {
	alert('I am in show_more function, webcenter: ' + webCenter + ' soa: ' + soa);
	if(webCenter == 1 && soa == 1){
		document.getElementById('soa_show_few').style.display = "none";
		document.getElementById('soa_show_more').style.display = "none";
		document.getElementById('webcenter_show_few').style.display = "none";
		document.getElementById('webcenter_show_more').style.display = "none";
		document.getElementById('none_show_few').style.display = "none";
		document.getElementById('none_show_more').style.display = "none";
		document.getElementById('websoa_show_few').style.display = "none";
		document.getElementById('websoa_show_more').style.display = "block";
	}
	else if (webCenter == 1 && soa == 0) {
		document.getElementById('soa_show_few').style.display = "none";
		document.getElementById('soa_show_more').style.display = "none";
		document.getElementById('webcenter_show_few').style.display = "none";
		document.getElementById('webcenter_show_more').style.display = "block";
		document.getElementById('none_show_few').style.display = "none";
		document.getElementById('none_show_more').style.display = "none";
		document.getElementById('websoa_show_few').style.display = "none";
		document.getElementById('websoa_show_more').style.display = "none";
	}
	else if (webCenter == 0 && soa == 1) {
		document.getElementById('soa_show_few').style.display = "none";
		document.getElementById('soa_show_more').style.display = "block";
		document.getElementById('webcenter_show_few').style.display = "none";
		document.getElementById('webcenter_show_more').style.display = "none";
		document.getElementById('none_show_few').style.display = "none";
		document.getElementById('none_show_more').style.display = "none";
		document.getElementById('websoa_show_few').style.display = "none";
		document.getElementById('websoa_show_more').style.display = "none";
	}
	else if (webCenter == 0 && soa == 0) { 
		alert("**************");
		document.getElementById('soa_show_few').style.display = "none";
		document.getElementById('soa_show_more').style.display = "none";
		document.getElementById('webcenter_show_few').style.display = "none";
		document.getElementById('webcenter_show_more').style.display = "none";
		document.getElementById('none_show_few').style.display = "none";
		document.getElementById('none_show_more').style.display = "block";
		document.getElementById('websoa_show_few').style.display = "none";
		document.getElementById('websoa_show_more').style.display = "none";
	}
}

function show_right_div(flag) {
	alert('show right div funtion');
	//alert("updated" + flag);
	//alert('flag' + flag);
	
	if (flag!=null && flag!="")
	{
		if (flag == 'few') {
			//alert('now load less');
			//alert('I am few');
			//alert("I was showing less, but more now, hheh");
			document.getElementById('switch_text').innerHTML = 'Show More >';
			show_few();
		}
		else {
			//alert('now load more');
			alert('I am more');
			
			document.getElementById('switch_text').innerHTML = 'Show Fewer >';
			show_more();	
		}
	}
}	



function getCookie(c_name)
{
	alert('cookie length = ' + document.cookie.length);
if (document.cookie.length>0)
  { 
  c_start=document.cookie.indexOf(c_name + "=");
  if (c_start!=-1)
    { 
    c_start=c_start + c_name.length+1 ;
    c_end=document.cookie.indexOf(";",c_start);
    if (c_end==-1) c_end=document.cookie.length
    return unescape(document.cookie.substring(c_start,c_end));
    } 
  }
return ""
}

function setCookie(c_name,value,expiredays)
{
	var exdate=new Date();
	exdate.setDate(exdate.getDate()+expiredays);
	document.cookie=c_name+ "=" +escape(value)+((expiredays==null) ? "" : "; expires="+exdate.toGMTString());
}

function checkCookie()
{
	username=getCookie('username');
	alert(username);
	if (username!=null && username!="")
	{
	  alert('Welcome again '+username+'!');
	  show_right_div(username);
	  setCookie('username',username,365);
	}
	else 
	{
		//alert('I am first time');
		username=flag;
		if (username!=null && username!="")
		{
			alert('I am setting the cookie');
			setCookie('username',username,365);
			
			if(webCenter == 1 && soa == 1){
				document.getElementById('soa_show_few').style.display = "none";
				document.getElementById('webcenter_show_few').style.display = "none";
				document.getElementById('none_show_few').style.display = "none";
				document.getElementById('websoa_show_few').style.display = "block";
			}
			else if (webCenter == 1 && soa == 0) {
				document.getElementById('soa_show_few').style.display = "none";
				document.getElementById('webcenter_show_few').style.display = "block";
				document.getElementById('none_show_few').style.display = "none";
				document.getElementById('websoa_show_few').style.display = "none";
			}
			else if (webCenter == 0 && soa == 1) {
				document.getElementById('soa_show_few').style.display = "block";
				document.getElementById('webcenter_show_few').style.display = "none";
				document.getElementById('none_show_few').style.display = "none";
				document.getElementById('websoa_show_few').style.display = "none";
			}
			else if (webCenter == 0 && soa == 0) { 
				document.getElementById('soa_show_few').style.display = "none";
				document.getElementById('webcenter_show_few').style.display = "none";
				document.getElementById('none_show_few').style.display = "block";
				document.getElementById('websoa_show_few').style.display = "none";
			}
		}
	}
}

