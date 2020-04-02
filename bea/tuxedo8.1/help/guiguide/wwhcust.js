// Copyright (c) 1999 Quadralay Corporation.  All rights reserved.
//
// The information in this file is confidential and proprietary to
// Quadralay Corporation.  Unauthorized use or duplication is
// strictly prohibited.

var tocalt=true                   // Option to display TOC Alt text

var fvexp=(356*24*60*60*1000);    // Favorite cookie expiration time
var maxfvs=10;                    // Maximum number of favorites per help set
var srtfvr=true;                  // Sort the favorites
var msgfvr="No Title";            // Default favorite title if not found

var srtndx=true;                  // Sort the index
var ndxbull="&shy;";              // Character to use as bullet in index

var msgsrch="No Title";           // Default search title if not found

var tff="Arial, sans-serif";      // Default font to use in tab panes
var tfs="1";                      // Default font size to use in tab panes

var dt="tab0";                    // The default tab range is tab0-tab3

// ****************** Do not edit below this line *********************

var hsmod=new Array;              // Array for multiple help sets

var srchhilite=false;             // Not implemented yet

var tbstrp="#FFFFFF";             // The tabstrip background color

var imgdir="./wwhgifs/";          // The image directory

var wwhdir="./";                  // The HTML file directory

var tab=new Array("tab0","tab1","tab2","tab3");

tab["tab0"]=new Array("display",0,"#FFFFFF","#FF0000","black","black");
tab["tab0"]["display"]=new Array(imgdir+"1b.gif",imgdir+"2a.gif",imgdir+"3a.gif",imgdir+"4a.gif");
tab["tab1"]=new Array("display",0,"#FFFFFF","#FF0000","black","black");
tab["tab1"]["display"]=new Array(imgdir+"1c.gif",imgdir+"2b.gif",imgdir+"3b.gif",imgdir+"4a.gif");
tab["tab2"]=new Array("display",0,"#FFFFFF","#FF0000","black","black");
tab["tab2"]["display"]=new Array(imgdir+"1a.gif",imgdir+"2c.gif",imgdir+"3c.gif",imgdir+"4b.gif");
tab["tab3"]=new Array("display",0,"#FFFFFF","#FF0000","black","black");
tab["tab3"]["display"]=new Array(imgdir+"1a.gif",imgdir+"2a.gif",imgdir+"3d.gif",imgdir+"4c.gif");

var showNavButtons=false;
var brwse=new Array("prev","next");
brwse["prev"]=new Array(imgdir+"prev_out.gif",imgdir+"prev_in.gif",imgdir+"prev_off.gif",imgdir+"prevover.gif",false);
brwse["next"]=new Array(imgdir+"next_out.gif",imgdir+"next_in.gif",imgdir+"next_off.gif",imgdir+"nextover.gif",false);

