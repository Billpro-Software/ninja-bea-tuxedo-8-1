VERSION 5.00
Begin VB.Form frmOpen 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Connect to M3 IIOP Listener"
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
      Left            =   1320
      MaxLength       =   32
      TabIndex        =   1
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
    gblnOpenSucceeded = False
    Me.Hide
End Sub

Private Sub cmdOK_Click()
    '
    ' Initialize the bootstrap object to connect it to
    ' the appropriate Iceberg domain.
    '
    Dim AuthorityType As Tobj_AuthType

    gobjBootstrap.Initialize "//" + txtNodeName.Text + ":" + txtPort.Text
    If frmTracing.checkErr("Bootstrap Initialize", tvMedium) = False Then
        MsgBox "Couldn't connect, try again!", , "Login"
        txtNodeName.SetFocus
        SendKeys "{Home}+{End}"
        Exit Sub
    End If
    
    
    ' If everything initialized OK, proceed
    gblnOpenSucceeded = True
    Me.Hide
    gblnGotBootstrap = True

    '
    ' Logged on, so disable the logon menu item and
    ' enable the other things
    '
    frmBrowser.Logon.Enabled = False
    frmBrowser.cmbCriteria.Enabled = True
    frmBrowser.cmdFind.Enabled = True
    frmBrowser.lstAvailable.Enabled = True
    frmBrowser.lvDetails.Enabled = True
    
End Sub

