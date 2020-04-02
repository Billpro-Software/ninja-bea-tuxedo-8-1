// Copyright (c) 1999 Quadralay Corporation.  All rights reserved.
//
// Originally based on and portions copyright (c) 1997, Marcelino 
// Alves Martins (martins@hks.com) "Folder-Tree" script which can 
// located at http://www.geocities.com/Paris/LeftBank/2178/

function Folder(folderDescription,hreference,topicID){ 
  this.desc=folderDescription;
  this.hreference=hreference;
  this.id=-1;
  this.navObj=0;
  this.iconImg=0;
  this.nodeImg=0;
  this.isLastNode=0;
  this.isOpen=true;
  this.iconSrc=imgdir+"tocfldo.gif";
  this.children=new Array;
  this.initialize=initializeFolder;
  this.setState=setFolderState;
  this.addChild=addChild;
  this.createIndex=createEntryIndex;
  this.hide=hideFolder;
  this.display=display;
  this.renderOb=drawFolder;
  this.totalHeight=totalHeight;
  this.subEntries=folderSubEntries;
  this.outputLink=outputFolderLink;
  this.type="Folder";
  this.leftSide="";
  this.initialized=false;
  if(topicID)this.topicID=topicID;
} 
 
function setFolderState(isOpen){ 
  if (isOpen==this.isOpen)return; 
  if (isNav4){ 
    var totalHeight=0; 
    for (var i=0;i<this.children.length;i++)totalHeight=totalHeight+this.children[i].navObj.clip.height; 
    if (this.isOpen)totalHeight=0-totalHeight; 
    for (var fIt=this.id+this.subEntries()+1;fIt<indexOfEntries.length;fIt++)indexOfEntries[fIt].navObj.moveBy(0,totalHeight); 
  }  
  this.isOpen=isOpen; 
  propagateChangesInState(this); 
} 
function propagateChangesInState(folder){   
  var i=0; 
  if(folder.isOpen){ 
    if(folder.nodeImg) 
      if(folder.isLastNode)folder.nodeImg.src=imgdir+"tocmlnde.gif"; 
      else folder.nodeImg.src=imgdir+"tocmnode.gif"; 
    folder.iconImg.src=imgdir+"tocfldo.gif"; 
    for(i=0;i<folder.children.length;i++)folder.children[i].display(); 
  }else{ 
    if(folder.nodeImg) 
      if(folder.isLastNode)folder.nodeImg.src=imgdir+"tocplnod.gif"; 
      else folder.nodeImg.src=imgdir+"tocpnode.gif"; 
    folder.iconImg.src=imgdir+"tocfldc.gif"; 
    for(i=0;i<folder.children.length;i++)folder.children[i].hide(); 
  }  
} 
function hideFolder(){ 
   if(isIE4)this.navObj.style.display="none"; 
   else if(isNav4)this.navObj.visibility="hide"; 
   this.setState(false); 
} 
function initializeFolder(level,lastNode,leftSide){ 
   var j=0;
   var i=0;
   var nc=this.children.length;
      
   this.createIndex();
   var auxEv=""; 
   if(isIE4||isNav4)auxEv="<a href='javascript:parent.clickOnNode("+this.id+")'>"; 
   else auxEv="<a>"; 
 
  if(level>0) 
    if(lastNode){ 
      this.leftSide=leftSide+auxEv+"<img name='nodeIcon"+this.id+"' src='"+imgdir+"tocmlnde.gif' width=16 height=22 border=0></a>"; 
      leftSide=leftSide+"<img src='"+imgdir+"tocblank.gif' width=16 height=22>";  
      this.isLastNode=1; 
    }else{ 
      this.leftSide=leftSide+auxEv+"<img name='nodeIcon"+this.id+"' src='"+imgdir+"tocmnode.gif' width=16 height=22 border=0></a>"; 
      leftSide=leftSide+"<img src='"+imgdir+"tocvline.gif' width=16 height=22>"; 
      this.isLastNode=0; 
      } 
  if (nc>0){ 
    level=level+1; 
    for(i=0;i<this.children.length;i++){ 
      if(i==this.children.length-1)this.children[i].initialize(level,true,leftSide); 
      else this.children[i].initialize(level,false,leftSide); 
      } 
  }
} 
function drawFolder(){ 
  if(isNav4){
    if(!tabDisplay.document.yPos)tabDisplay.document.yPos=0;
    tabDisplay.document.write("\n<layer id='folder"+this.id+"' top="+tabDisplay.document.yPos+" visibility=hide>"); 
  }
  tabDisplay.document.write("\n\t<table ");
  if(isIE4)tabDisplay.document.write(" id='folder"+this.id+"' style='position:block;' ");
  tabDisplay.document.write(" border=0 cellspacing=0 cellpadding=0>");
  tabDisplay.document.write("\n\t\t<tr>\n\t\t\t<td");
  // put the IE blur code in here to get rid of the box around the node icon afer a click
  tabDisplay.document.write(">");
  tabDisplay.document.write(this.leftSide);
  this.outputLink();
  tabDisplay.document.write("<img name='folderIcon" + this.id + "' ");
  if(tocalt)tabDisplay.document.write("alt='"+this.desc+"' ");
  tabDisplay.document.write("src='"+this.iconSrc+"' border=0></a>");
  tabDisplay.document.write("</td>\n\t\t\t<td valign=middle nowrap><font  face='"+parent.tff+"' size="+parent.tfs+">"); 
  if(useTOCTextLinks){
    this.outputLink(); 
    tabDisplay.document.write(this.desc+"</a>"); 
  }else tabDisplay.document.write(this.desc); 
  tabDisplay.document.write("</font></td>");  
  tabDisplay.document.write("\n\t\t</tr>\n\t</table>"); 
  if(isNav4)tabDisplay.document.write("\n</layer>"); 
  if(isIE4){ 
    this.navObj=tabDisplay.document.all["folder"+this.id]; 
    this.iconImg=tabDisplay.document.all["folderIcon"+this.id]; 
    this.nodeImg=tabDisplay.document.all["nodeIcon"+this.id]; 
  }else if(isNav4){ 
    this.navObj=tabDisplay.document.layers["folder"+this.id]; 
    this.iconImg=this.navObj.document.images["folderIcon"+this.id]; 
    this.nodeImg=this.navObj.document.images["nodeIcon"+this.id]; 
    tabDisplay.document.yPos=tabDisplay.document.yPos+this.navObj.clip.height; 
  }
} 
function outputFolderLink(){ 
  if(this.hreference){ 
    tabDisplay.document.write("<a href='javascript:parent.displayTOCSelection(\""+this.hreference+"\")'"); 
    if(isIE4||isNav4)tabDisplay.document.write("onClick='javascript:parent.clickOnFolder("+this.id+")'"); 
    tabDisplay.document.write(">"); 
  }else tabDisplay.document.write("<a>"); 
} 
function addChild(childNode){ 
  this.children[this.children.length]=childNode; 
  return childNode; 
} 
function folderSubEntries(){ 
  var i=0; 
  var se=this.children.length; 
  for (i=0;i<this.children.length;i++)if(this.children[i].children)se=se+this.children[i].subEntries(); 
  return se; 
} 
function Item(itemDescription,itemLink,topicID){ 
  this.desc=itemDescription;
  this.link=itemLink;
  this.id=-1;
  this.navObj=0;
  this.iconImg=0;
  this.iconSrc=imgdir+"tocdoc.gif";
  this.initialize=initializeItem;
  this.createIndex=createEntryIndex;
  this.hide=hideItem;
  this.display=display;
  this.renderOb=drawItem;
  this.totalHeight=totalHeight;
  this.type="Item";
  this.isSelected=false;
  this.leftSide="";
  this.topicID=topicID;
} 
function hideItem(){ 
  if(isIE4)this.navObj.style.display="none"; 
  else this.navObj.visibility="hide"; 
} 
function initializeItem(level, lastNode, leftSide){
  this.createIndex();
  if(level>0)
    if(lastNode){
      this.leftSide=leftSide+"<img src='"+imgdir+"toclnode.gif' width=16 height=22>";
      leftSide=leftSide+"<img src='"+imgdir+"tocblank.gif' width=16 height=22>";
    }else{
      this.leftSide=leftSide + "<img src='"+imgdir+"tocnode.gif' width=16 height=22>";
      leftSide=leftSide+"<img src='"+imgdir+"tocvline.gif' width=16 height=22>";
    }else this.renderOb("");
}
function drawItem(){
  if(isNav4)tabDisplay.document.write("\n<layer id='item"+this.id+"' top="+tabDisplay.document.yPos+" visibility=hide>");
  tabDisplay.document.write("\n\t<table ");
  if(isIE4)tabDisplay.document.write(" id='item"+this.id+"' style='position:block;' ");
  tabDisplay.document.write(" border=0 cellspacing=0 cellpadding=0>");
  tabDisplay.document.write("\n\t\t<tr>\n\t\t\t<td>");
  tabDisplay.document.write(this.leftSide);
  tabDisplay.document.write("<a href='javascript:parent.displayTOCSelection(\""+this.link+"\")'>");
  tabDisplay.document.write("<img id='itemIcon"+this.id+"' ");
  if(tocalt)tabDisplay.document.write("alt='"+this.desc+"' ");
  tabDisplay.document.write("src='"+this.iconSrc+"' border=0>");
  tabDisplay.document.write("</a>");
  tabDisplay.document.write("</td>\n\t\t\t<td valign=middle nowrap><font face='"+parent.tff+"' size="+parent.tfs+">");
  if(useTOCTextLinks)tabDisplay.document.write("<a href='javascript:parent.displayTOCSelection(\""+this.link+"\")'>"+this.desc+"</a>");
  else tabDisplay.document.write(this.desc);
  tabDisplay.document.write("</td>\n\t\t</tr>\n\t</table>");
  if(isNav4)tabDisplay.document.write("\n</layer>");
  if(isIE4){
    this.navObj = tabDisplay.document.all["item"+this.id];
    this.iconImg = tabDisplay.document.all["itemIcon"+this.id];
  }else if(isNav4){
    this.navObj = tabDisplay.document.layers["item"+this.id];
    this.iconImg = this.navObj.document.images["itemIcon"+this.id];
    tabDisplay.document.yPos=tabDisplay.document.yPos+this.navObj.clip.height;
  }
}
function display(){
  if(isIE4)this.navObj.style.display="block";
  else this.navObj.visibility="show";
}
function createEntryIndex(){
   this.id=indexOfEntries.length;
   indexOfEntries[indexOfEntries.length]=this;
}
function totalHeight(){
  var h=this.navObj.clip.height;
  if (this.isOpen)for(var i=0;i<this.children.length;i++)h=h+this.children[i].totalHeight();
  return h;
}
function clickOnNode(folderId){
  var clickedFolder=indexOfEntries[folderId];
  clickedFolder.setState(!clickedFolder.isOpen);
}
function clickOnFolder(folderId){
   var clicked=indexOfEntries[folderId];
   if(!clicked.isOpen)clickOnNode(folderId);
} 
function displayTOC(){
   tabDisplay.document.yPos=0;
   foldersTree.renderOb();
   foldersTree.display();
   for (var i=1;i<indexOfEntries.length;i++){
      folderOpen[i]=false;
      if (indexOfEntries[i].type=="Folder"){
         folderOpen[i]=indexOfEntries[i].isOpen;
         indexOfEntries[i].isOpen=true;
      }
      indexOfEntries[i].renderOb();
   }
   if(isNav4)tabDisplay.document.write("\n<layer top="+indexOfEntries[indexOfEntries.length-1].navObj.top+">&nbsp;\n</layer>");
   foldersTree.setState(false);
   if(foldersTree.initialized){for(var i=0;i<indexOfEntries.length;i++)if(folderOpen[i])indexOfEntries[i].setState(true);}
   else foldersTree.setState(true);
   foldersTree.initialized=true;
}



//**************************************************************** 
// You are free to copy the "Folder-Tree" script as long as you  
// keep this copyright notice: 
// Script found in: http://www.geocities.com/Paris/LeftBank/2178/ 
// Author: Marcelino Alves Martins (martins@hks.com) December '97. 
//**************************************************************** 
