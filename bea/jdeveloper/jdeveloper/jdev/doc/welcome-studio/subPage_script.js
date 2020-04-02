
var dropdown_order = 0;
var page_index = 0;
var drop_open = false;
var myPar = location.href.split('?');
var divideAgain = myPar[1].split('&');
var divideAgainAgain = divideAgain[0].split('=');
var webCenter = divideAgainAgain[1];

divideAgainAgain = divideAgain[1].split('=');
var soa = divideAgainAgain[1];



function mouse_over_home(id) {
	document.getElementById(id).className = "go_home_down";
	parentArrowImgObj.src = parentArrowButtonOverSrc;
	
}
function mouse_out_home(id) {
	document.getElementById(id).className = "go_home_init";	
	parentArrowImgObj.src = parentArrowButtonEnabledSrc;
}
function mouse_down_home(id) {
	document.getElementById(id).className = "go_home_down";	
}

function MM_findObj(n, d) { //v4.01
  var p,i,x;  if(!d) d=document; if((p=n.indexOf("?"))>0&&parent.frames.length) {
    d=parent.frames[n.substring(p+1)].document; n=n.substring(0,p);}
  if(!(x=d[n])&&d.all) x=d.all[n]; for (i=0;!x&&i<d.forms.length;i++) x=d.forms[i][n];
  for(i=0;!x&&d.layers&&i<d.layers.length;i++) x=MM_findObj(n,d.layers[i].document);
  if(!x && d.getElementById) x=d.getElementById(n); return x;
}
function MM_nbGroup(event, grpName) { //v6.0
var i,img,nbArr,args=MM_nbGroup.arguments;
  if (event == "init" && args.length > 2) {
    if ((img = MM_findObj(args[2])) != null && !img.MM_init) {
      img.MM_init = true; img.MM_up = args[3]; img.MM_dn = img.src;
      if ((nbArr = document[grpName]) == null) nbArr = document[grpName] = new Array();
      nbArr[nbArr.length] = img;
      for (i=4; i < args.length-1; i+=2) if ((img = MM_findObj(args[i])) != null) {
        if (!img.MM_up) img.MM_up = img.src;
        img.src = img.MM_dn = args[i+1];
        nbArr[nbArr.length] = img;
    } }
  } else if (event == "over") {
    document.MM_nbOver = nbArr = new Array();
    for (i=1; i < args.length-1; i+=3) if ((img = MM_findObj(args[i])) != null) {
      if (!img.MM_up) img.MM_up = img.src;
      img.src = (img.MM_dn && args[i+2]) ? args[i+2] : ((args[i+1])?args[i+1] : img.MM_up);
      nbArr[nbArr.length] = img;
    }
  } else if (event == "out" ) {
    for (i=0; i < document.MM_nbOver.length; i++) { img = document.MM_nbOver[i]; img.src = (img.MM_dn) ? img.MM_dn : img.MM_up; }
  } else if (event == "down") {
    nbArr = document[grpName];
    if (nbArr) for (i=0; i < nbArr.length; i++) { img=nbArr[i]; img.src = img.MM_up; img.MM_dn = 0; }
    document[grpName] = nbArr = new Array();
    for (i=2; i < args.length-1; i+=2) if ((img = MM_findObj(args[i])) != null) {
      if (!img.MM_up) img.MM_up = img.src;
      img.src = img.MM_dn = (args[i+1])? args[i+1] : img.MM_up;
      nbArr[nbArr.length] = img;
  } }
}

function MM_preloadImages() { //v3.0
  var d=document; if(d.images){ if(!d.MM_p) d.MM_p=new Array();
    var i,j=d.MM_p.length,a=MM_preloadImages.arguments; for(i=0; i<a.length; i++)
    if (a[i].indexOf("#")!=0){ d.MM_p[j]=new Image; d.MM_p[j++].src=a[i];}}
}

//////////////// MY SCRIPT //////////////// 

//HOME BUTTON
//on mouseout MM_nbGroup('out');
//on mouseover MM_nbGroup('over','welcome_r2_c2','welcomeImages/welcome_r2_c2_f4.png','','welcome_r2_c3','welcomeImages/welcome_r2_c3_f2.png','',1);	
//on click = MM_nbGroup('down','navbar1','welcome_r2_c2','welcomeImages/welcome_r2_c2_f3.png','welcome_r2_c3','welcomeImages/welcome_r2_c3_f5.png',1);	
	
// DROPDOWN BUTTON
//on mouseout MM_nbGroup('out');MM_startTimeout();
//on mouseover MM_showMenu(window.mm_menu_0829143011_0,0,22,null,'welcome_r2_c3');MM_nbGroup('over','welcome_r2_c3','welcomeImages/welcome_r2_c3_f2.png','','welcome_r2_c2','welcomeImages/welcome_r2_c2_f2.png','',1);
//on click = MM_nbGroup('down','navbar1','welcome_r2_c2','welcomeImages/welcome_r2_c2_f2.png',1);  	

function geto(id){
	//alert(id);
	var obj = document.getElementById(id);
	return obj;
	}

/// ABSOLUTE POSITION; returns: TOP, LEFT, TOP && LEFT, HEIGHT, TOP+HEIGHT, 	
var abso = {
	t:function(o) {
			var offTrail = o;
			var offTop = 0;
			
			while (offTrail) {
				offTop += offTrail.offsetTop;
				offTrail = offTrail.offsetParent;
			}
			return (offTop); 
		},
	l:function(o) {
			var offTrail = o;
			var offLeft = 0;
			
			while (offTrail) {
				offLeft += offTrail.offsetLeft;
				offTrail = offTrail.offsetParent;
			}
			return (offLeft); 
		},
	tl:function(o) {
		var offTrail = o;
		var offLeft = 0;
		var offTop = 0;
		while (offTrail) {
			offLeft += offTrail.offsetLeft;
			offTop += offTrail.offsetTop;
			offTrail = offTrail.offsetParent;
		}
		return {tt:offTop , ll:offLeft}; 
	},
	h:function(o) {
		var hh = o.offsetHeight;
		return(hh);
		},
	th:function(o) {
		var hhtt = abso.t(o)+abso.h(o);
		return(hhtt);
		},
	w:function(o) {
		var w = o.offsetWidth;
		return(w);
		},
	lw:function(o) {
		var lw = abso.l(o)+o.offsetWidth;
		return(lw);
		}	
};	

var mouseout = true;
var menuOpen = false;	
var drop = null;

function iniDrop(txt, id){
	
	//alert(txt);

	var parentArrowImgObj = geto('dropButton');
	var parentHomeImgObj = geto('homeImg');
	
	var parentArrowButtonEnabledSrc = 'welcomeImages/welcome_r2_c3.png';
	var parentArrowButtonOverSrc = 'welcomeImages/welcome_r2_c3_f2.png';
	
	var parentHome_only_ButtonOverSrc = 'welcomeImages/welcome_r2_c2_f4.png';
	
	var parentHomeButtonOverSrc = 'welcomeImages/welcome_r2_c2_f2.png';
	var parentHomeButtonEnabledSrc = "welcomeImages/welcome_r2_c2.png";

	parentArrowImgObj.onmouseover = function(){
		drop_open = true;
		mouseout = false;
		handleOut(false);
		if(drop == null){
			makedrop(this.id, txt);
			menuOpen = true;	
		}else{
			drop.style.display = '';
			menuOpen = true;
				
		}
		this.src = parentArrowButtonOverSrc;
		document.getElementById(id).className = "go_home_over";	
		
	}
	parentArrowImgObj.onmouseout = function(){
		if(menuOpen == false){
			this.src = parentArrowButtonEnabledSrc;
			mouse_out_home(id);
		}
		mouse_out_home(id);
		mouseout = true;
		handleOut(true);

	}
}
	
	var parentHomeImgObj = null;
	var parentArrowImgObj = null;
	var parentArrowButtonEnabledSrc = null;
	var parentArrowButtonOverSrc = null;
	var parentHomeButtonOverSrc = null;
	var parentHomeButtonEnabledSrc	= null;
	var menuArray = new Array();
	
function makedrop(oid, txt){
	
	parentArrowImgObj = geto('dropButton');
	parentHomeImgObj = geto('homeImg');

	parentArrowButtonEnabledSrc = 'welcomeImages/welcome_r2_c3.png';
	parentArrowButtonOverSrc = 'welcomeImages/welcome_r2_c3_f2.png';
	
	parentHomeButtonOverSrc = 'welcomeImages/welcome_r2_c2_f2.png';
	parentHomeButtonEnabledSrc = "welcomeImages/welcome_r2_c2.png";

	var o = parentArrowImgObj;
	
	var t = abso.t(o)-2; 
	var hh = abso.h(o)-2;
	var tt = (t+hh)-2;
	var ll = abso.l(o);	
	
	
	if(drop == null){
	var parent_div = document.createElement('DIV');
	
		parent_div.id = 'parent_div';
		
		parent_div.style.position = 'absolute';
		parent_div.style.width = 139+'px';
		parent_div.style.top = tt+'px';
		parent_div.style.left = ll+'px';
		parent_div.style.border = '1px solid #999999';
		parent_div.style.background = '#FFFFFF';
		
		parent_div.style.backgroundImage = 'url(welcomeImages/spacer.gif)';
		
		parent_div.style.zIndex = 6000;
	/**/	
		parent_div.onmouseover = function(){
			mouseout = false;
			handleOut(false);
		
		}
		parent_div.onmousemove = function(){
			handleOut(false);
		
		}
		parent_div.onmouseout = function(){
			mouseout = true;
		
		}
		
	var cont_div = document.createElement('DIV');
	
		cont_div.style.position = 'relative';
		cont_div.style.width = 138+'px';
		cont_div.style.overflow = 'hidden';
		
		cont_div.style.borderTop = '1px solid #FFFFFF';
		cont_div.style.borderLeft = '1px solid #FFFFFF';
		cont_div.style.borderBottom = '1px solid #CCCCCC';
		cont_div.style.borderRight = '1px solid #CCCCCC';
	

	
	if (txt == 'BA') {
		
		menuArray[0] = { menuname:"Model Applications ", menulink:'window.open(\'model_applications.html\');', linkonly:'model_applications.html', menutarget:'_blank'};
		menuArray[1] = { menuname:"Design Databases ", menulink:'window.open(\'welcome2.html\');',linkonly:'welcome2.html', menutarget:'_blank' };
		menuArray[2] = { menuname:"Integrate Applications ", menulink:'window.open(\'welcome3.html\');',linkonly:'welcome3.html', menutarget:'_blank' };
		page_index = 1;
	}
	if (txt == 'DD') {
		
		menuArray[0] = { menuname:"Model Applications ", menulink:'window.open(\'build_applications.html\');', linkonly:'build_applications.html', menutarget:'_blank'};
		menuArray[1] = { menuname:"Build Applications ", menulink:'window.open(\'welcome2.html\');',linkonly:'welcome2.html', menutarget:'_blank' };
		menuArray[2] = { menuname:"Integrate Applications ", menulink:'window.open(\'welcome3.html\');',linkonly:'welcome3.html', menutarget:'_blank' };
		
		page_index = 2;
	}
	if (txt == 'MA') {
		
		menuArray[0] = { menuname:"Design Databases ", menulink:'window.open(\'build_applications.html\');', linkonly:'build_applications.html', menutarget:'_blank'};
		menuArray[1] = { menuname:"Build Applications ", menulink:'window.open(\'welcome2.html\');',linkonly:'welcome2.html', menutarget:'_blank' };
		menuArray[2] = { menuname:"Integrate Applications ", menulink:'window.open(\'welcome3.html\');',linkonly:'welcome3.html', menutarget:'_blank' };
		
		page_index = 3;
	}
	if (txt == 'IA') {
		
		menuArray[0] = { menuname:"Model Applications ", menulink:'window.open(\'build_applications.html\');', linkonly:'build_applications.html', menutarget:'_blank'};
		menuArray[1] = { menuname:"Design Databases ", menulink:'window.open(\'welcome2.html\');',linkonly:'welcome2.html', menutarget:'_blank' };
		menuArray[2] = { menuname:"Build Applications ", menulink:'window.open(\'welcome3.html\');',linkonly:'welcome3.html', menutarget:'_blank' };
		
		page_index = 4;
	}
	
	
	var cdiv = makeMenuItems(cont_div);
		
		parent_div.appendChild(cdiv);
		document.body.appendChild(parent_div);
		
		drop = parent_div;
		}
	menuOpen = false;	
}
function makeMenuItems(cont_div){
	var divo = cont_div;
	for(var i = 0; i < menuArray.length; i++){
		var menuname = menuArray[i].menuname;
		var menulink = menuArray[i].menulink;
		var menutarget = menuArray[i].menutarget;
		var linkonly = menuArray[i].linkonly;
		dropdown_order = i;
                //var menuItemDiv = new Array;
		var menuItemDiv = makeMenuItem(menuname, menulink, menutarget);
			divo.appendChild(menuItemDiv);
	}
	return divo;
}

function makeMenuItem(v){
	var mitem = document.createElement('DIV');
		mitem.style.position = 'relative';
		mitem.style.width = 135+'px';
		mitem.style.height = 18+'px';
		mitem.style.paddingLeft = 4+'px';
                mitem.style.paddingTop = 2+'px';
		mitem.style.cursor = 'hand';
		
		var MALink = "model_applications.html?oracle.webcenter.framework=" + webCenter + "&oracle.sca.modeler=" + soa;
		var DDLink = "design_databases.html?oracle.webcenter.framework=" + webCenter + "&oracle.sca.modeler=" + soa;
		var BALink = "build_applications.html?oracle.webcenter.framework=" + webCenter + "&oracle.sca.modeler=" + soa;
		var IALink = "integrate_applications.html?oracle.webcenter.framework=" + webCenter + "&oracle.sca.modeler=" + soa;
		
                //mtiem.onclick=alert('yeah');
		if (dropdown_order==0)
                {
                mitem.onmouseup = function(){
				//eval(menulink);
				//alert('yeah');
					if(page_index == 1) window.location = MALink;
					if(page_index == 2) window.location = MALink;
					if(page_index == 3) window.location = DDLink;
					if(page_index == 4) window.location = MALink;
				}
        }
                if (dropdown_order==1)
                {
                mitem.onmouseup = function(){
				//eval(menulink);
				//alert('yeah');
					if(page_index == 1) window.location = DDLink;
					if(page_index == 2) window.location = BALink;
					if(page_index == 3) window.location = BALink;
					if(page_index == 4) window.location = DDLink;
				 

			}
                }
                if (dropdown_order==2)
                {
                mitem.onmouseup = function(){
					if(page_index == 1) window.location = IALink;
					if(page_index == 2) window.location = IALink;
					if(page_index == 3) window.location = IALink;
					if(page_index == 4) window.location = BALink;

			}
                }
                
                /*
                if (dropdown_order==0)
                {
                mitem.title = 'Model Applications';
                }
                if (dropdown_order==1)
                {
                mitem.title = 'Design Databases';
                }
                if (dropdown_order==2)
                {
                mitem.title = 'Integrate Applications';
                }
                if (dropdown_order==3)
                {
                mitem.title = 'Explore JDeveloper';
                }
		*/
		mitem.className = 'menuItemEna';
		mitem.style.borderBottom = '1px solid #CCCCCC';
	var mitemText = document.createTextNode(v);	
		mitem.appendChild(mitemText);
		
		mitem.onmousemove = function(){
			handleOut(false);

		}
		
		mitem.onmouseover = function(){
			mouseout = false;
			handleOut(false);
			this.className = 'menuItemOver';
		}
		
		mitem.onmousedown = function(){
			this.className = 'menuItemOver';
			//document.target.
		}
		
		mitem.onmouseout = function(){
			mouseout = true;
			handleOut(true);
			this.className = 'menuItemEna';
			
		}
		
	
return mitem;
}

function hidepanel(){
	if(mouseout == true){
	var o = document.getElementById('parent_div');
		o.style.display = 'none';
	parentArrowImgObj.src = parentArrowButtonEnabledSrc;
	parentHomeImgObj.src = parentHomeButtonEnabledSrc;
	menuOpen = false;
	}else{
		return false;
	}
}

var to = null;

function handleOut(v){

	if(to != null || v == false){
		window.clearTimeout(to);
		to = null;
		return;
	}else{
		window.setTimeout('hidepanel()', 800);
		return;
	}	
}