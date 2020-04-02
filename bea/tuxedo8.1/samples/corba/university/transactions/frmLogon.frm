VERSION 5.00
Begin VB.Form frmLogon 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Login"
   ClientHeight    =   2844
   ClientLeft      =   2832
   ClientTop       =   3480
   ClientWidth     =   4404
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1677.073
   ScaleMode       =   0  'User
   ScaleWidth      =   4128.512
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   390
      Left            =   2340
      TabIndex        =   6
      Top             =   2100
      Width           =   1140
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   390
      Left            =   732
      TabIndex        =   5
      Top             =   2100
      Width           =   1140
   End
   Begin VB.TextBox txtClientName 
      Height          =   345
      Left            =   1800
      TabIndex        =   4
      Top             =   1560
      Width           =   2325
   End
   Begin VB.TextBox txtSystemPassword 
      Height          =   345
      IMEMode         =   3  'DISABLE
      Left            =   1800
      PasswordChar    =   "*"
      TabIndex        =   3
      Top             =   1080
      Width           =   2325
   End
   Begin VB.TextBox txtUserName 
      Height          =   345
      Left            =   1800
      TabIndex        =   1
      Top             =   135
      Width           =   2325
   End
   Begin VB.TextBox txtApplicationPassword 
      Height          =   345
      IMEMode         =   3  'DISABLE
      Left            =   1800
      PasswordChar    =   "*"
      TabIndex        =   2
      Top             =   600
      Width           =   2325
   End
   Begin VB.Label Label2 
      Caption         =   "&Client Name:"
      Height          =   252
      Left            =   120
      TabIndex        =   9
      Top             =   1560
      Width           =   1452
   End
   Begin VB.Label Label1 
      Caption         =   "&System Password:"
      Height          =   252
      Left            =   120
      TabIndex        =   0
      Top             =   1080
      Width           =   1452
   End
   Begin VB.Label lblLabels 
      Caption         =   "&User Name:"
      Height          =   270
      Index           =   0
      Left            =   105
      TabIndex        =   8
      Top             =   150
      Width           =   1080
   End
   Begin VB.Label lblLabels 
      Caption         =   "&Application Password:"
      Height          =   276
      Index           =   1
      Left            =   120
      TabIndex        =   7
      Top             =   600
      Width           =   1680
   End
End
Attribute VB_Name = "frmLogon"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'      Copyright (c) 1998 BEA Systems, Inc.
'      All rights reserved
'
'      THIS IS UNPUBLISHED PROPRIETARY
'      SOURCE CODE OF BEA Systems, Inc.
'      The copyright notice above does not
'      evidence any actual or intended
'      publication of such source code.
'
' #ident       "@(#) Tests/Clients/University1/frmLogon.bas    $Revision: 1.1 $"

' frmLogon.bas : Logon form for University1 example VB client


Option Explicit
#If Security Then

Public LogonSucceeded As Boolean

Private Sub cmdCancel_Click()
    'set the global var to false
    'to denote a failed login
    LogonSucceeded = False
    Me.Hide
End Sub

Private Sub cmdOK_Click()
    Dim logonStatus As Security_AuthenticationStatus
    Dim UserData(0) As Byte
    Dim exc As Variant
    
    logonStatus = oPrincAuth.Logon( _
                        txtUserName.Text, _
                        txtClientName.Text, _
                        txtApplicationPassword.Text, _
                        txtSystemPassword.Text, _
                        UserData, exc)
    ' Check for and handle any exceptions first, then check for error returns
    If exc <> Empty Then
        If (frmTracing.checkException(exc, "Logon", "logon", tvMedium)) Then
            If TypeOf exc Is DICORBASystemException Then
                MsgBox "CORBA System Exception occurred", , "Login"
            Else
                MsgBox "Unknown exception occurred", , "Login"
            End If
            LogonSucceeded = False
            Me.Hide
            Exit Sub
        End If
    ElseIf logonStatus <> SecAuthSuccess Then
        If logonStatus = SecAuthContinue Then
            MsgBox "Logon failed, status = SecAuthContinue", , "Login"
        ElseIf logonStatus = SecAuthExpired Then
            MsgBox "Logon failed, status = SecAuthExpired", , "Login"
        ElseIf logonStatus = SecAuthFailure Then
            MsgBox "Logon failed, status = SecAuthFailure", , "Login"
        Else
            MsgBox "Logon failed, status = <unknown>", , "Login"
        End If
        LogonSucceeded = False
        Me.Hide
        Exit Sub
    Else
        LogonSucceeded = True
    End If
End Sub
#End If
