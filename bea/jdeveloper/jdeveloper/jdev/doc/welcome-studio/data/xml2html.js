try
{
var files = WScript.Arguments;

var xml1=new ActiveXObject("Microsoft.XMLDOM");
var xsl1=new ActiveXObject("Microsoft.XMLDOM");
            
var xml2=new ActiveXObject("Microsoft.XMLDOM");
var xsl2=new ActiveXObject("Microsoft.XMLDOM"); 
WScript.Echo("start");
//WScript.Echo(files(1));
//WScript.Echo(files(2));
//WScript.Echo(files(3));

xml1.async = false;
xml1.load(files(0));
xsl1.async = false;
xsl1.load(files(1));

xml2.async = false;
xml2.load(files(2));
xsl2.async = false;
xsl2.load(files(3));

for(i=0;i<xml2.documentElement.childNodes.length;i++)
{
    xml1.documentElement.appendChild(xml2.documentElement.childNodes[i].cloneNode(1))
}

//fso1 = new ActiveXObject("Scripting.FileSystemObject");
//fout1 = fso1.CreateTextFile("test.xml", true);
//fout1.write(xml1.xml);


var  res=xml1.transformNode(xsl1);  
   
fso = new ActiveXObject("Scripting.FileSystemObject");
fout = fso.CreateTextFile(files(4), true);
fout.write(res);

WScript.Echo("success");

WScript.Quit(0);

}

catch(e)

{

WScript.Echo(e.message);
WScript.Quit(0);

} 