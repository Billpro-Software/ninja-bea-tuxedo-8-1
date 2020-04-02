<?xml version="1.0" encoding="utf-8"?>

<xsl:transform version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:output method="html" encoding="utf-8" doctype-public="-//W3C//DTD XHTML 1.0 Transitional//EN" doctype-system="http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd"/>

<xsl:template match="/">
<html xsl:version="1.0" 
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
    xmlns="http://www.w3.org/1999/xhtml" 
    xmlns:xi="http://www.w3.org/2001/XInclude" >

<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
<style type="text/css">
#footer{
	height: 65px;
	position: fixed;
	bottom: 0;
	left: 0;
	width: 100%;
	background-color:#FFFFFF;
	font-size: 13px;
	font-family:Verdana, Arial, Helvetica, sans-serif;
}

#footer_content{
	background-color:#9da3ad;
	height: 33px;
	vertical-align: middle;
}
#links{
	margin-top: 5px;
	width: 700px;
	margin-left: 7px;
}
#copyRight_block {
	background-color:#FFFFFF;
	margin-top:1px;
	height:20px;
	font-family: Tahoma;
}
A.bottomBannerItem{
	font-size: 12px;
	color: #333333;
	text-decoration:none;
	font-family: Tahoma;
}
A.bottomBannerItem:hover {
	font-size: 12px;
	color: #003399;
	text-decoration:none;
	font-family: Tahoma;
}
A.bottomBannerItem:focus {
	font-size: 12px;
	color: #999999;
	text-decoration:none;
	font-family: Tahoma;
}

A.copyRight:link{
	color: #666666;
	font-size:9px;
	text-decoration:none;
	margin-left: 7px;
	font-family: Tahoma;
}
A.copyRight:hover{
	color: #003399;
	font-size:9px;
	text-decoration:none;
	font-family: Tahoma;
}
A.copyRight:focus{
	color: #999999;
	font-size:9px;
	text-decoration:none;
	font-family: Tahoma;
}
#each_item {
	color:#FFFFFF;
}

</style>
	
</head>

<body>
	<div id="footer">
  		<div id="footer_content">
			<div id="links">
                <xsl:for-each select="model_application/buttom_menu/buttom_item">
					<a class="bottomBannerItem"  href="{@link}" style="text-decoration:none;">
                    	<span><xsl:value-of select="buttom_item_name"/></span>
					</a>
                    <xsl:if test="position() != last()">
                        <span style="color:#ffffff; font-family:arial; font-size:10px;"> | </span> 
                    </xsl:if>  
                </xsl:for-each>
			</div>
        </div>
		<div id="copyRight_block">
			<a href="custom:jdevShowHelpInWindow:help_legalnotices_html" class="copyRight">Copyright © 1997, 2010 Oracle and/or its affiliates. All rights reserved.</a>
		</div>
    </div>
</body>
</html>

</xsl:template>
</xsl:stylesheet>