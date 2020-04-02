@echo off
REM
REM $Id: wasunreg.cmd,v 1.2 2000/07/06 23:32:49 gtong Exp $
REM
REM This batch command file unregisters the java classes
REM previously registered as ActiveX components. 
REM
REM
javareg /q /unregister /class:bea.jolt.pool.UserInfo
javareg /q /unregister /class:bea.jolt.pool.asp.AspPoolManagerConfig
javareg /q /unregister /class:bea.jolt.pool.asp.AspSessionPoolManager
javareg /q /unregister /class:bea.jolt.pool.asp.AspDataSet
javareg /q /unregister /class:bea.jolt.pool.asp.AspTemplate
javareg /q /unregister /class:bea.jolt.pool.asp.UserInfo
javareg /q /unregister /class:bea.jolt.pool.asp.TemplateData
javareg /q /unregister /class:bea.jolt.pool.asp.Template
javareg /q /unregister /class:bea.jolt.pool.asp.SessionPoolManager
