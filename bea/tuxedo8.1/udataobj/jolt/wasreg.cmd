@echo off
REM
REM $Id: wasreg.cmd,v 1.2 2000/07/06 23:32:38 gtong Exp $
REM
REM This batch command file registers the necessary java
REM classes as ActiveX components so that they are accessible
REM from Active Server Pages or any other ActiveX client.
REM The classes (or equivalent zip file) must exists
REM in your java/Trustlib directory (normally C:\%WINDIR%\java\Trustlib.
REM
javareg /q /register /class:bea.jolt.pool.asp.UserInfo		/progid:BEAWEB.UserInfo
javareg /q /register /class:bea.jolt.pool.asp.SessionPoolManager /progid:BEAWEB.SessionPoolManager
javareg /q /register /class:bea.jolt.pool.asp.Template		/progid:BEAWEB.Template
javareg /q /register /class:bea.jolt.pool.asp.TemplateData	/progid:BEAWEB.TemplateData
REM
REM These are the new ActiveX component names.
REM
javareg /q /register /class:bea.jolt.pool.UserInfo		/progid:BEAJOLTPOOL.AspUserInfo
javareg /q /register /class:bea.jolt.pool.asp.AspPoolManagerConfig   /progid:BEAJOLTPOOL.AspPoolManagerConfig
javareg /q /register /class:bea.jolt.pool.asp.AspSessionPoolManager /progid:BEAJOLTPOOL.AspSessionPoolManager
javareg /q /register /class:bea.jolt.pool.asp.AspTemplate	/progid:BEAJOLTPOOL.AspTemplate
javareg /q /register /class:bea.jolt.pool.asp.AspDataSet	/progid:BEAJOLTPOOL.AspDataSet
