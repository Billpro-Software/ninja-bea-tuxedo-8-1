VERSION 5.00
Begin VB.Form frmOpen 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Open"
   ClientHeight    =   1548
   ClientLeft      =   1572
   ClientTop       =   3612
   ClientWidth     =   3756
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   912.837
   ScaleMode       =   0  'User
   ScaleWidth      =   3521.047
   ShowInTaskbar   =   0   'False
   Visible         =   0   'False
   Begin VB.TextBox txtNodeName 
      Height          =   345
      Left            =   1290
      MaxLength       =   32
      TabIndex        =   1
      Text            =   "todd"
      Top             =   135
      Width           =   2325
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   390
      Left            =   495
      TabIndex        =   4
      Top             =   1020
      Width           =   1140
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   390
      Left            =   2100
      TabIndex        =   5
      Top             =   1020
      Width           =   1140
   End
   Begin VB.TextBox txtPort 
      Height          =   345
      IMEMode         =   3  'DISABLE
      Left            =   1320
      MaxLength       =   9
      TabIndex        =   3
      Text            =   "2500"
      Top             =   525
      Width           =   2325
   End
   Begin VB.Label lblLabels 
      Caption         =   "&Node Name:"
      Height          =   270
      Index           =   0
      Left            =   105
      TabIndex        =   0
      Top             =   150
      Width           =   1080
   End
   Begin VB.Label lblLabels 
      Caption         =   "&Port:"
      Height          =   270
      Index           =   1
      Left            =   105
      TabIndex        =   2
      Top             =   540
      Width           =   1080
   End
End
Attribute VB_Name = "frmOpen"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'      Copyright (c) 1997,1998 BEA Systems, Inc.
'      All rights reserved
'
'      THIS IS UNPUBLISHED PROPRIETARY
'      SOURCE CODE OF BEA Systems, Inc.
'      The copyright notice above does not
'      evidence any actual or intended
'      publication of such source code.
'
' #ident       "@(#) Tests/Clients/SimpApp/frmOpen.bas    $Revision: 1.1 $"

' frmOpen.bas : Open form for University1 example VB client

Option Explicit

Private Sub cmdCancel_Click()
    'set the global var to false to denote a failed login
    OpenSucceeded = False
    Me.Hide
End Sub

Private Sub cmdOK_Click()
    '
    ' Initialize the bootstrap object to connect it to
    ' the appropriate Iceberg domain.
    '
    oBootstrap.Initialize "//" + txtNodeName.Text + ":" + txtPort.Text
    If frmTracing.checkErr("Bootstrap Initialize", tvMedium) = False Then
        MsgBox "Couldn't connect, try again!", , "Login"
        txtNodeName.SetFocus
        SendKeys "{Home}+{End}"
        Exit Sub
    End If
    
#If Security Then

    On Error Resume Next
    Set oSecurityCurrent = oBootstrap.CreateObject("Tobj.SecurityCurrent")
    If frmTracing.checkErr("Creating Security Current", tvMedium) = False Then
        MsgBox "Couldn't get security object!", , "Login"
        OpenSucceeded = False
        Me.Hide
        Exit Sub
    End If
    
    On Error Resume Next
    Set oPrincAuth = oSecurityCurrent.principal_authenticator
    If frmTracing.checkErr("Getting principal authenticator", tvMedium) = False Then
        MsgBox "Couldn't get authenticator!", , "Login"
        OpenSucceeded = False
        Me.Hide
        Exit Sub
    End If
    
    AuthorityType = oPrincAuth.get_auth_type
    '
    ' If Authorization type indicates an application password, prompt for it
    '
    If AuthorityType = TOBJ_APPAUTH Then
        '
        ' Prompt for passwords
        '
        frmLogon.Show vbModal
    End If
    '
    ' Need to check status of login
    '
#End If
    
    '
    ' Get an object reference to a factory finder object
    '
    Set oBsFactoryFinder = oBootstrap.CreateObject("Tobj.FactoryFinder")
    If frmTracing.checkErr("Creating Factory Finder", tvMedium) = False Then
        MsgBox "Couldn't create, try again!", , "Login"
        txtNodeName.SetFocus
        SendKeys "{Home}+{End}"
        Exit Sub
    End If

    '
    ' Get a teller factory object from the factory finder
    '
    Set oRegistrarFactory = oBsFactoryFinder.find_one_factory_by_id(RegistrarFactoryID)
    If frmTracing.checkErr("Finding Registrar Factory", tvMedium) = False Then
        MsgBox "Couldn't find, try again!", , "Login"
        txtNodeName.SetFocus
        SendKeys "{Home}+{End}"
        Exit Sub
    End If
    
    '
    ' Have the Registrar factory create a new registrar object
    '
    Set oRegistrar = oRegistrarFactory.find_registrar(exc)
    ' Check for and handle any exceptions
    If (frmTracing.checkException(exc, "Finding registrar", "find_registrar", tvMedium)) Then
        If TypeOf exc Is DICORBASystemException Then
            MsgBox "CORBA System Exception occurred"
        Else
            MsgBox "Unknown exception occurred"
        End If
        MsgBox "Couldn't find registrar, try again!", , "Login"
        txtNodeName.SetFocus
        SendKeys "{Home}+{End}"
        Exit Sub
    End If

    ' If everything created OK, proceed
    OpenSucceeded = True
    Me.Hide
    gotBootstrap = True

    '
    ' Logged on, so disable the logon menu item and
    ' enable the other things
    '
    frmBrowser.Logon.Enabled = False
    frmBrowser.Logoff.Enabled = True
    frmBrowser.cmbCriteria.Enabled = True
    frmBrowser.cmdAddToDetails.Enabled = True
    frmBrowser.cmdFind.Enabled = True
    frmBrowser.lstAvailable.Enabled = True
    frmBrowser.lvDetails.Enabled = True
    
End Sub
