<?xml version="1.0" encoding="utf-8"?>

<xsl:transform version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:output method="html" encoding="utf-8" doctype-public="-//W3C//DTD XHTML 1.0 Transitional//EN"/>

<xsl:template match="/">
<html xsl:version="1.0" 
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
    xmlns="http://www.w3.org/1999/xhtml" 
    xmlns:xi="http://www.w3.org/2001/XInclude" >

<head>
<title>Build Applications</title>
<style type="text/css">
	BODY {
		font-family:Tohoma;
		font-size:11pt;
		background-color:#FFFFFF;
		color:#006699;
	}
	TABLE {
		border:none;
		border-width:0px;
		padding:0px;
		vertical-align:top;
		font-family:Tohoma;
		font-size:11pt;
	}
	TR {
		vertical-align:top;
	}
	#each_block {
		color: #006666;
		position:relative;
		width: 247px;
		text-align: left;
		padding: 3px;
	}
	.menuItemEna{
		font-family:Arial, Helvetica, sans-serif;
		font-size:11px;
		font-weight:normal;
		color:#000000;
		background-color: #F0F0F0;
	}
	.menuItemOver{
		font-family:Arial, Helvetica, sans-serif;
		font-size:11px;
		font-weight:normal;
		color:#FFFFFF;
		background-color: #316AC4;
	}
	#header_text {
		font-family: Verdana, Arial, Helvetica, sans-serif;
		font-size: 11px;
		font-style: normal;
		font-weight: bold;
		color: #003399;
	}
	#each_item_even {
		padding:0px;
		width: 100%;
		background-color:#f3f3f3;
	}
	#each_item_odd {
		padding:0px;
		width: 100%;
		background-color:#FFFFFF;
	}
	#item_content{
		display:block;
		margin-bottom:7px;
		margin-top: 3px;
		margin-left:20px;
	}
	#icon_area {
		margin-top:4px;
		width: 20px;
	}
	#instructional {
		font-family: Verdana, Arial, Helvetica, sans-serif;
		font-size: 11px;
		font-weight: normal;
		color: #666666;
	}
	#title_text{
		color:#000000;
		font-size:11px;
		font-family: Verdana, Arial, Helvetica, sans-serif;
		position:absolute;
		top:5px;
		left: 64px;
		width:324px;
		top:7px;
	}
	#title_area {
		position:absolute; 
		top:0px; 
		left:0px;
		z-index:50;
	}
	#coming_soon {
		color:#3366FF;
		font-size:11px;
		font-family: Verdana, Arial, Helvetica, sans-serif;
		font-weight: bold;
	}
	#show_link {
		font-family: Verdana, Arial, Helvetica, sans-serif;
		color:#003399;
		font-size:11px;
		text-align:right;
	}
	#category_title {
		background-color:#dcdcdc;
		width:100%;
		height: 28px;
		color:#000000;
		font-size:11px;
		font-family: Tahoma, Kalimati, FreeSans, Verdana, Arial, sans-serif;
		font-weight:bold;
	}
	a:link {
		text-decoration:none;
		color:#003399;
	}
	a:visited {
		text-decoration:none;
		color:#003399;
	}
	a:hover {
		text-decoration:none;
	}
	a:focus {
		text-decoration:none;
		color:#003399;
	}
	IMG {
		vertical-align: text-top;
	}
	#show_fewer{
		z-index:-1;
	}
	#Show_more{
		z-index:-1;
		position:absolute;
		left:0px;
		top:40px;
		width:100%;
	}
	#websoa_show_more{
		z-index:-1;
		position:absolute;
		left:0px;
		top:40px;
		width:100%;
		display:none;
	}
#footer{
	height: 55px;
	position: fixed;
	bottom: 0;
	left: 0;
	width: 100%;
	background-color:#FFFFFF;
	font-size: 13px;
	font-family:Tahoma, Kalimati, FreeSans, Verdana, Arial, sans-serif;
}


#footer_content{
	background-color:#9da3ad;
	height: 33px;
	vertical-align: middle;
}
#links{
	margin-top: 10px;
	width: 100%;
	min-width:800px;
}
#copyRight_block {
	background-color:#FFFFFF;
	margin-top:5px;
	height:20px;
	font-family: Tahoma, Kalimati, FreeSans, Verdana, Arial, sans-serif;
}
A.bottomBannerItem{
	font-size: 12px;
	color: #ffffff;
	text-decoration:none;
	font-family: Tahoma, Kalimati, FreeSans, Verdana, Arial, sans-serif;
}
A.bottomBannerItem:hover {
	font-size: 12px;
	color: #003399;
	text-decoration:none;
	font-family: Tahoma, Kalimati, FreeSans, Verdana, Arial, sans-serif;
}
A.bottomBannerItem:focus {
	font-size: 12px;
	color: #003399;
	text-decoration:none;
	font-family: Tahoma, Kalimati, FreeSans, Verdana, Arial, sans-serif;
}

A.copyRight:link{
	color: #333333;
	font-size:9px;
	text-decoration:none;
	margin-left: 7px;
	font-family: Tahoma, Kalimati, FreeSans, Verdana, Arial, sans-serif;
}
A.copyRight:hover{
	color: #003399;
	font-size:9px;
	text-decoration:none;
	font-family: Tahoma, Kalimati, FreeSans, Verdana, Arial, sans-serif;
}
A.copyRight:focus{
	color: #003399;
	font-size:9px;
	text-decoration:none;
	font-family: Tahoma, Kalimati, FreeSans, Verdana, Arial, sans-serif;
}
#each_item {
	color:#FFFFFF;
}
#seperator {
	color:#ffffff; 
	font-family:arial; 
	font-size:10px;
}
#go_home {
	margin-left:4px;
	margin-top:2px;
	font-size:11px;
	font-family: Tahoma, Kalimati, FreeSans, Verdana, Arial, sans-serif;
	height:21px;
	width:35px;
}
.go_home_init {
	color:#000000;
	border:thin;
	border-color:#ffffff;
	border-style:solid;
	border-width:1px;
	background:#ffffff;
}
.go_home_over {
	color:#000000;
	border:thin;
	border-color:#a7a7a7;
	border-style:solid;
	border-width:1px;
	background:#efefef;
}
.go_home_down{
	color:#ffffff;
	border:thin;
	border-color:#a7a7a7;
	border-style:solid;
	border-width:1px;
	background:#316ac4;
}
#home_text{
	margin-left:5px;
	margin-top:3px;
}
A#home_link:link{
	color:#000000;
	text-decoration:none;
}
A#home_link:active{
	color:#ffffff;
	text-decoration:none;
}
</style>

<script language="JavaScript" type="text/javascript" src="subPage_script.js"></script>
<script language="JavaScript" type="text/javascript" src="startPage_script.js"></script>
<script language="javascript" type="text/javascript" src="add_cookie.js"></script>

</head>

    
<body onLoad="checkCookie(); iniDrop('BA', 'go_home'); MM_preloadImages('welcomeImages/navigation_r1_c1_f2.png','welcomeImages/navigation_r1_c1_f3.png','welcomeImages/navigation_r1_c5_f2.png','welcomeImages/navigation_r1_c5_f3.png','welcomeImages/navigation_r1_c8_f2.png','welcomeImages/navigation_r1_c8_f3.png','welcomeImages/navigation_r1_c10_f2.png','welcomeImages/navigation_r1_c10_f3.png','welcomeImages/navigation_r1_c12_f2.png','welcomeImages/navigation_r1_c12_f3.png','welcomeImages/navigation_r2_c1_f2.png','welcomeImages/navigation_r2_c1_f3.png')">

<!--HEADER BEGIN-->
<div id="title_area">
<table width="100%" cellpadding="0" cellspacing="0" border="0">
    <tr>
        <td>
            <a target="_parent" id="home_link" onclick="gotoLink('welcome.html');">
                <div class="go_home_init" id="go_home" onmouseover="mouse_over_home('go_home');" onmousedown="mouse_down_home('go_home');" onmouseout="mouse_out_home('go_home');">
                    <div id="home_text">Home</div>
                </div>
            </a>
        </td>
        <td><img id="dropButton" name="welcome_r2_c3" src="welcomeImages/welcome_r2_c3.png" width="24" height="25" border="0" alt="" /></td>
        <td width="100%"><span id="title_text" style="top:7px; font-size: 11px"><strong><xsl:value-of select="start_page/@name" /></strong></span></td>
    </tr>

</table>

</div>


	<br />
   	
   	<div id="show_link" onclick="hideAndShow();"> <a href="#"> <span id="switch_text">Show More > </span></a> </div>

<!--Soa = 1 Webcenter = 0>-->

	<div id="soa_show_few" style="display:none;">  
		<table>
			<xsl:for-each select="start_page/main_items/item[@soa = 1 and @studio = 1]">
				<xsl:if test="position() mod 2 != 0" >
					<xsl:variable name="cur" select='position()' />
					<tr>
						<td>
							<div id="icon_area">
								<img>
									<xsl:attribute name="src">
									<xsl:value-of select="icon"/>
									</xsl:attribute>
								</img>
							</div>
						</td>
						<td width="247" onmouseover="this.style.backgroundColor='#d8ecfd';" onmouseout="this.style.backgroundColor='white';">
							<xsl:if test="@status = '1'">
								<a href="{@link}" style="text-decoration:none;">
								<div id="each_block">
									<span id="header_text"><xsl:value-of select="name" /></span><br />
									<span id="instructional"><xsl:value-of select="description" /></span><br />
								</div>
								</a>
							</xsl:if>
							<xsl:if test="@status = '0'">
								<div id="each_block">
									<span id="header_text"><xsl:value-of select="name" /></span>
									<span id="coming_soon">- Coming Soon</span>
									<br />
									<span id="instructional"><xsl:value-of select="description" /></span><br />
								</div>
							</xsl:if>
						</td>
						<td width="16">
						</td>
						<td>
							<xsl:for-each select="../../main_items/item[@soa = 1]">
								<xsl:variable name="find_next" select="$cur + 1" />
								<xsl:if test="position() = $find_next" >
									<td>
										<div id="icon_area">
											<img>
												<xsl:attribute name="src">
												<xsl:value-of select="icon"/>
												</xsl:attribute>
											</img>
										</div>
									</td>
								   <td width="247" onmouseover="this.style.backgroundColor='#d8ecfd';" onmouseout="this.style.backgroundColor='white';">
										<xsl:if test="@status = '1'">
											<a href="{@link}" style="text-decoration:none;">
											<div id="each_block">
												<span id="header_text"><xsl:value-of select="name" /></span><br />
												<span id="instructional"><xsl:value-of select="description" /></span><br />
											</div>
											</a>
										</xsl:if>
										<xsl:if test="@status = '0'">
											<div id="each_block">
												<span id="header_text"><xsl:value-of select="name" /></span>
												<span id="coming_soon">- Coming Soon</span>
												<br />
												<span id="instructional"><xsl:value-of select="description" /></span><br />
											</div>
										</xsl:if>
								  </td>
									
								</xsl:if>
							</xsl:for-each>
						</td> 
						   
					</tr> 
				</xsl:if>
			</xsl:for-each>
            <tr>
            	<td height="55"></td>
            </tr>
		</table>
	</div>
   
	<div id="soa_show_more" style="display:none;">
		<table width="100%" border="0" align="left" cellpadding="0" cellspacing="0">
			<xsl:for-each select="start_page/main_items[@soatitle = 1]">
				<tr>
					<td colspan="2"><div id="category_title"><div style="margin-left:5px; margin-top:7px;"><xsl:value-of select="@name"/></div></div></td>
				</tr>
				<xsl:for-each select="item[@studio = 1]" >
					<xsl:choose>
						<xsl:when test="position() mod 2 = 0">
							<tr id="each_item_even">
								<td width="100%" onmouseover="this.style.backgroundColor='#d8ecfd';" onmouseout="this.style.backgroundColor='#f3f3f3';">
									<table width="100%">
										<tr>
											<td width="20">
												<div id="icon_area">
													<img>
														<xsl:attribute name="src">
														<xsl:value-of select="icon"/>
														</xsl:attribute>
													</img>
												</div>
											</td>
											<td>
												<div id="item_content">
													<xsl:if test="@status = '1'">
														<a href="{@link}" style="text-decoration:none;">
														<span id="header_text"><xsl:value-of select="name" /></span><br />
														<span id="instructional"><xsl:value-of select="description" /></span><br />
														</a>
													</xsl:if>
													<xsl:if test="@status = '0'">
														<span id="header_text"><xsl:value-of select="name" /></span>
														<span id="coming_soon">- Coming Soon</span>
														<br />
														<span id="instructional"><xsl:value-of select="description" /></span><br />
													</xsl:if>
												</div>
											</td>
										</tr>
									</table>
								</td>
							</tr>
						</xsl:when>
						<xsl:otherwise>
							<tr id="each_item_odd">
								<td width="100%" onmouseover="this.style.backgroundColor='#d8ecfd';" onmouseout="this.style.backgroundColor='#ffffff';">
									<table width="100%">
										<tr>
											<td width="20">
												<div id="icon_area">
													<img>
														<xsl:attribute name="src">
														<xsl:value-of select="icon"/>
														</xsl:attribute>
													</img>
												</div>
											</td>
											<td>
												<div id="item_content">
													<xsl:if test="@status = '1'">
														<a href="{@link}" style="text-decoration:none;">
														<span id="header_text"><xsl:value-of select="name" /></span><br />
														<span id="instructional"><xsl:value-of select="description" /></span><br />
														</a>
													</xsl:if>
													<xsl:if test="@status = '0'">
														<span id="header_text"><xsl:value-of select="name" /></span>
														<span id="coming_soon">- Coming Soon</span>
														<br />
														<span id="instructional"><xsl:value-of select="description" /></span><br />
													</xsl:if>
												</div>
											</td>
										</tr>
									</table>
							  	</td>
							</tr>
						</xsl:otherwise>
					</xsl:choose>
				</xsl:for-each>
			</xsl:for-each>
            <tr>
            	<td height="55"></td>
            </tr>
		</table>   
    </div>
    
    
    
    
    <div id="webcenter_show_few" style="display:none;">
	<!--select="start_page/main_items/item[@priority = 1]">-->
		<table>
			<xsl:for-each select="start_page/main_items/item[@webcenter = 1 and @studio = 1]">
				<xsl:if test="position() mod 2 != 0" >
					<xsl:variable name="cur" select='position()' />
					<tr>
						<td>
							<div id="icon_area">
								<img>
									<xsl:attribute name="src">
									<xsl:value-of select="icon"/>
									</xsl:attribute>
								</img>
							</div>
						</td>
						<td width="247" onmouseover="this.style.backgroundColor='#d8ecfd';" onmouseout="this.style.backgroundColor='white';">
							<xsl:if test="@status = '1'">
								<a href="{@link}" style="text-decoration:none;">
								<div id="each_block">
									<span id="header_text"><xsl:value-of select="name" /></span><br />
									<span id="instructional"><xsl:value-of select="description" /></span><br />
								</div>
								</a>
							</xsl:if>
							<xsl:if test="@status = '0'">
								<div id="each_block">
									<span id="header_text"><xsl:value-of select="name" /></span>
									<span id="coming_soon">- Coming Soon</span>
									<br />
									<span id="instructional"><xsl:value-of select="description" /></span><br />
								</div>
							</xsl:if>
						</td>
						<td width="16">
						</td>
						<td>
							<xsl:for-each select="../../main_items/item[@webcenter = 1]">
								<xsl:variable name="find_next" select="$cur + 1" />
								<xsl:if test="position() = $find_next" >
									<td>
										<div id="icon_area">
											<img>
												<xsl:attribute name="src">
												<xsl:value-of select="icon"/>
												</xsl:attribute>
											</img>
										</div>
									</td>
								   <td width="247" onmouseover="this.style.backgroundColor='#d8ecfd';" onmouseout="this.style.backgroundColor='white';">
										<xsl:if test="@status = '1'">
											<a href="{@link}" style="text-decoration:none;">
											<div id="each_block">
												<span id="header_text"><xsl:value-of select="name" /></span><br />
												<span id="instructional"><xsl:value-of select="description" /></span><br />
											</div>
											</a>
										</xsl:if>
										<xsl:if test="@status = '0'">
											<div id="each_block">
												<span id="header_text"><xsl:value-of select="name" /></span>
												<span id="coming_soon">- Coming Soon</span>
												<br />
												<span id="instructional"><xsl:value-of select="description" /></span><br />
											</div>
										</xsl:if>
								  </td>
									
								</xsl:if>
							</xsl:for-each>
						</td> 
						   
					</tr> 
				</xsl:if>
			</xsl:for-each>
            <tr>
            	<td height="55"></td>
            </tr>
		</table>
	</div>
   
	<div id="webcenter_show_more" style="display:none;">
		<table width="100%" border="0" align="left" cellpadding="0" cellspacing="0">
			<xsl:for-each select="start_page/main_items[@webcentertitle = 1]">
				<tr>
					<td colspan="2"><div id="category_title"><div style="margin-left:5px; margin-top:7px;"><xsl:value-of select="@name"/></div></div></td>
				</tr>
				<xsl:for-each select="item[@studio = 1]" >
					<xsl:choose>
						<xsl:when test="position() mod 2 = 0">
							<tr id="each_item_even">
								<td width="100%" onmouseover="this.style.backgroundColor='#d8ecfd';" onmouseout="this.style.backgroundColor='#f3f3f3';">
									<table width="100%">
										<tr>
											<td width="20">
												<div id="icon_area">
													<img>
														<xsl:attribute name="src">
														<xsl:value-of select="icon"/>
														</xsl:attribute>
													</img>
												</div>
											</td>
											<td>
												<div id="item_content">
													<xsl:if test="@status = '1'">
														<a href="{@link}" style="text-decoration:none;">
														<span id="header_text"><xsl:value-of select="name" /></span><br />
														<span id="instructional"><xsl:value-of select="description" /></span><br />
														</a>
													</xsl:if>
													<xsl:if test="@status = '0'">
														<span id="header_text"><xsl:value-of select="name" /></span>
														<span id="coming_soon">- Coming Soon</span>
														<br />
														<span id="instructional"><xsl:value-of select="description" /></span><br />
													</xsl:if>
												</div>
											</td>
										</tr>
									</table>
								</td>
							</tr>
						</xsl:when>
						<xsl:otherwise>
							<tr id="each_item_odd">
								<td width="100%" onmouseover="this.style.backgroundColor='#d8ecfd';" onmouseout="this.style.backgroundColor='#ffffff';">
									<table width="100%">
										<tr>
											<td width="20">
												<div id="icon_area">
													<img>
														<xsl:attribute name="src">
														<xsl:value-of select="icon"/>
														</xsl:attribute>
													</img>
												</div>
											</td>
											<td>
												<div id="item_content">
													<xsl:if test="@status = '1'">
														<a href="{@link}" style="text-decoration:none;">
														<span id="header_text"><xsl:value-of select="name" /></span><br />
														<span id="instructional"><xsl:value-of select="description" /></span><br />
														</a>
													</xsl:if>
													<xsl:if test="@status = '0'">
														<span id="header_text"><xsl:value-of select="name" /></span>
														<span id="coming_soon">- Coming Soon</span>
														<br />
														<span id="instructional"><xsl:value-of select="description" /></span><br />
													</xsl:if>
												</div>
											</td>
										</tr>
									</table>
							  	</td>
							</tr>
						</xsl:otherwise>
					</xsl:choose>
				</xsl:for-each>
			</xsl:for-each>
            <tr>
            	<td height="55"></td>
            </tr>
		</table>   
    </div>
    
    
    <div id="none_show_few" style="display:none;">
	<!--select="start_page/main_items/item[@priority = 1]">-->
		<table>
			<xsl:for-each select="start_page/main_items/item[@webcenter = 1 and @soa = 1 and @studio = 1]">
				<xsl:if test="position() mod 2 != 0" >
					<xsl:variable name="cur" select='position()' />
					<tr>
						<td>
							<div id="icon_area">
								<img>
									<xsl:attribute name="src">
									<xsl:value-of select="icon"/>
									</xsl:attribute>
								</img>
							</div>
						</td>
						<td width="247" onmouseover="this.style.backgroundColor='#d8ecfd';" onmouseout="this.style.backgroundColor='white';">
							<xsl:if test="@status = '1'">
								<a href="{@link}" style="text-decoration:none;">
								<div id="each_block">
									<span id="header_text"><xsl:value-of select="name" /></span><br />
									<span id="instructional"><xsl:value-of select="description" /></span><br />
								</div>
								</a>
							</xsl:if>
							<xsl:if test="@status = '0'">
								<div id="each_block">
									<span id="header_text"><xsl:value-of select="name" /></span>
									<span id="coming_soon">- Coming Soon</span>
									<br />
									<span id="instructional"><xsl:value-of select="description" /></span><br />
								</div>
							</xsl:if>
						</td>
						<td width="16">
						</td>
						<td>
							<xsl:for-each select="../../main_items/item[@webcenter = 1 and @soa = 1]">
								<xsl:variable name="find_next" select="$cur + 1" />
								<xsl:if test="position() = $find_next" >
									<td>
										<div id="icon_area">
											<img>
												<xsl:attribute name="src">
												<xsl:value-of select="icon"/>
												</xsl:attribute>
											</img>
										</div>
									</td>
								   <td width="247" onmouseover="this.style.backgroundColor='#d8ecfd';" onmouseout="this.style.backgroundColor='white';">
										<xsl:if test="@status = '1'">
											<a href="{@link}" style="text-decoration:none;">
											<div id="each_block">
												<span id="header_text"><xsl:value-of select="name" /></span><br />
												<span id="instructional"><xsl:value-of select="description" /></span><br />
											</div>
											</a>
										</xsl:if>
										<xsl:if test="@status = '0'">
											<div id="each_block">
												<span id="header_text"><xsl:value-of select="name" /></span>
												<span id="coming_soon">- Coming Soon</span>
												<br />
												<span id="instructional"><xsl:value-of select="description" /></span><br />
											</div>
										</xsl:if>
								  </td>
									
								</xsl:if>
							</xsl:for-each>
						</td> 
						   
					</tr> 
				</xsl:if>
			</xsl:for-each>
            <tr>
            	<td height="55"></td>
            </tr>
		</table>
	</div>
   
	<div id="none_show_more" style="display:none;">
		<table width="100%" border="0" align="left" cellpadding="0" cellspacing="0">
			<xsl:for-each select="start_page/main_items[@soatitle = 1 and @webcentertitle = 1]">
				<tr>
					<td colspan="2"><div id="category_title"><div style="margin-left:5px; margin-top:7px;"><xsl:value-of select="@name"/></div></div></td>
				</tr>
				<xsl:for-each select="item[@studio = 1]" >
					<xsl:choose>
						<xsl:when test="position() mod 2 = 0">
							<tr id="each_item_even">
								<td width="100%" onmouseover="this.style.backgroundColor='#d8ecfd';" onmouseout="this.style.backgroundColor='#f3f3f3';">
									<table width="100%">
										<tr>
											<td width="20">
												<div id="icon_area">
													<img>
														<xsl:attribute name="src">
														<xsl:value-of select="icon"/>
														</xsl:attribute>
													</img>
												</div>
											</td>
											<td>
												<div id="item_content">
													<xsl:if test="@status = '1'">
														<a href="{@link}" style="text-decoration:none;">
														<span id="header_text"><xsl:value-of select="name" /></span><br />
														<span id="instructional"><xsl:value-of select="description" /></span><br />
														</a>
													</xsl:if>
													<xsl:if test="@status = '0'">
														<span id="header_text"><xsl:value-of select="name" /></span>
														<span id="coming_soon">- Coming Soon</span>
														<br />
														<span id="instructional"><xsl:value-of select="description" /></span><br />
													</xsl:if>
												</div>
											</td>
										</tr>
									</table>
								</td>
							</tr>
						</xsl:when>
						<xsl:otherwise>
							<tr id="each_item_odd">
								<td width="100%" onmouseover="this.style.backgroundColor='#d8ecfd';" onmouseout="this.style.backgroundColor='#ffffff';">
									<table width="100%">
										<tr>
											<td width="20">
												<div id="icon_area">
													<img>
														<xsl:attribute name="src">
														<xsl:value-of select="icon"/>
														</xsl:attribute>
													</img>
												</div>
											</td>
											<td>
												<div id="item_content">
													<xsl:if test="@status = '1'">
														<a href="{@link}" style="text-decoration:none;">
														<span id="header_text"><xsl:value-of select="name" /></span><br />
														<span id="instructional"><xsl:value-of select="description" /></span><br />
														</a>
													</xsl:if>
													<xsl:if test="@status = '0'">
														<span id="header_text"><xsl:value-of select="name" /></span>
														<span id="coming_soon">- Coming Soon</span>
														<br />
														<span id="instructional"><xsl:value-of select="description" /></span><br />
													</xsl:if>
												</div>
											</td>
										</tr>
									</table>
							  	</td>
							</tr>
						</xsl:otherwise>
					</xsl:choose>
				</xsl:for-each>
			</xsl:for-each>
            <tr>
            	<td height="55"></td>
            </tr>
		</table>  
    </div>
    
    
    <div id="websoa_show_few" style="display:none;">
    		<table>
			<xsl:for-each select="start_page/main_items/item[@priority = 1 and @studio = 1]">
				<xsl:if test="position() mod 2 != 0" >
					<xsl:variable name="cur" select='position()' />
					<tr>
						<td>
							<div id="icon_area">
								<img>
									<xsl:attribute name="src">
									<xsl:value-of select="icon"/>
									</xsl:attribute>
								</img>
							</div>
						</td>
						<td width="247" onmouseover="this.style.backgroundColor='#d8ecfd';" onmouseout="this.style.backgroundColor='white';">
							<xsl:if test="@status = '1'">
								<a href="{@link}" style="text-decoration:none;">
								<div id="each_block">
									<span id="header_text"><xsl:value-of select="name" /></span><br />
									<span id="instructional"><xsl:value-of select="description" /></span><br />
								</div>
								</a>
							</xsl:if>
							<xsl:if test="@status = '0'">
								<div id="each_block">
									<span id="header_text"><xsl:value-of select="name" /></span>
									<span id="coming_soon">- Coming Soon</span>
									<br />
									<span id="instructional"><xsl:value-of select="description" /></span><br />
								</div>
							</xsl:if>
						</td>
						<td width="16">
						</td>
						<td>
							<xsl:for-each select="../../main_items/item[@priority = 1 and @studio = 1]">
								<xsl:variable name="find_next" select="$cur + 1" />
								<xsl:if test="position() = $find_next" >
									<td>
										<div id="icon_area">
											<img>
												<xsl:attribute name="src">
												<xsl:value-of select="icon"/>
												</xsl:attribute>
											</img>
										</div>
									</td>
								   <td width="247" onmouseover="this.style.backgroundColor='#d8ecfd';" onmouseout="this.style.backgroundColor='white';">
										<xsl:if test="@status = '1'">
											<a href="{@link}" style="text-decoration:none;">
											<div id="each_block">
												<span id="header_text"><xsl:value-of select="name" /></span><br />
												<span id="instructional"><xsl:value-of select="description" /></span><br />
											</div>
											</a>
										</xsl:if>
										<xsl:if test="@status = '0'">
											<div id="each_block">
												<span id="header_text"><xsl:value-of select="name" /></span>
												<span id="coming_soon">- Coming Soon</span>
												<br />
												<span id="instructional"><xsl:value-of select="description" /></span><br />
											</div>
										</xsl:if>
								  </td>
									
								</xsl:if>
							</xsl:for-each>
						</td> 
						   
					</tr> 
				</xsl:if>
			</xsl:for-each>
            <tr>
            	<td height="55"></td>
            </tr>
		</table>
    </div>
    
    <div id="websoa_show_more" style="display:none;">
		<table width="100%" border="0" align="left" cellpadding="0" cellspacing="0">
			<xsl:for-each select="start_page/main_items">
				<tr>
					<td colspan="2"><div id="category_title"><div style="margin-left:5px; margin-top:7px;"><xsl:value-of select="@name"/></div></div></td>
				</tr>
				<xsl:for-each select="item[@studio = 1]" >
					<xsl:choose>
						<xsl:when test="position() mod 2 = 0">
							<tr id="each_item_even">
								<td width="100%" onmouseover="this.style.backgroundColor='#d8ecfd';" onmouseout="this.style.backgroundColor='#f3f3f3';">
									<table width="100%">
										<tr>
											<td width="20">
												<div id="icon_area">
													<img>
														<xsl:attribute name="src">
														<xsl:value-of select="icon"/>
														</xsl:attribute>
													</img>
												</div>
											</td>
											<td>
												<div id="item_content">
													<xsl:if test="@status = '1'">
														<a href="{@link}" style="text-decoration:none;">
														<span id="header_text"><xsl:value-of select="name" /></span><br />
														<span id="instructional"><xsl:value-of select="description" /></span><br />
														</a>
													</xsl:if>
													<xsl:if test="@status = '0'">
														<span id="header_text"><xsl:value-of select="name" /></span>
														<span id="coming_soon">- Coming Soon</span>
														<br />
														<span id="instructional"><xsl:value-of select="description" /></span><br />
													</xsl:if>
												</div>
											</td>
										</tr>
									</table>
								</td>
							</tr>
						</xsl:when>
						<xsl:otherwise>
							<tr id="each_item_odd">
								<td width="100%" onmouseover="this.style.backgroundColor='#d8ecfd';" onmouseout="this.style.backgroundColor='#ffffff';">
									<table width="100%">
										<tr>
											<td width="20">
												<div id="icon_area">
													<img>
														<xsl:attribute name="src">
														<xsl:value-of select="icon"/>
														</xsl:attribute>
													</img>
												</div>
											</td>
											<td>
												<div id="item_content">
													<xsl:if test="@status = '1'">
														<a href="{@link}" style="text-decoration:none;">
														<span id="header_text"><xsl:value-of select="name" /></span><br />
														<span id="instructional"><xsl:value-of select="description" /></span><br />
														</a>
													</xsl:if>
													<xsl:if test="@status = '0'">
														<span id="header_text"><xsl:value-of select="name" /></span>
														<span id="coming_soon">- Coming Soon</span>
														<br />
														<span id="instructional"><xsl:value-of select="description" /></span><br />
													</xsl:if>
												</div>
											</td>
										</tr>
									</table>
							  	</td>
							</tr>
						</xsl:otherwise>
					</xsl:choose>
				</xsl:for-each>
			</xsl:for-each>
            <tr>
            	<td height="55"></td>
            </tr>
		</table>   
    </div>
    
    
    <div id="footer">
  		<div id="footer_content">
			<div id="links">
                <span><xsl:text disable-output-escaping="yes">&amp;#160;</xsl:text></span>
                <xsl:for-each select="start_page/buttom_menu/buttom_item">
					<a class="bottomBannerItem"  href="{@link}" >
                    	<span><xsl:value-of select="buttom_item_name"/></span>
					</a>
                    <xsl:if test="position() != last()">
                        <span id="seperator"> | </span>
                    </xsl:if>  
                </xsl:for-each>
			</div>
        </div>
		<!--new new-->
		<div id="copyRight_block">
			<a href="custom:jdevShowHelpInWindow:help_legalnotices_html" class="copyRight">Copyright <xsl:text disable-output-escaping="yes">&amp;#169;</xsl:text>  1997, 2010 Oracle and/or its affiliates. All rights reserved.</a>
		</div>
		<!--end of new new-->
    </div>
</body>
  
</html>
</xsl:template>
</xsl:transform>