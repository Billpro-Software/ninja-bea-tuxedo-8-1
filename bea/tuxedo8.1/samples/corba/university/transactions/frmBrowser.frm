VERSION 5.00
Object = "{5E9E78A0-531B-11CF-91F6-C2863C385E30}#1.0#0"; "MSFLXGRD.OCX"
Object = "{3B7C8863-D78F-101B-B9B5-04021C009402}#1.1#0"; "RICHTX32.OCX"
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.2#0"; "COMCTL32.OCX"
Object = "{F2F6FD17-DABA-11D1-9B02-0000F8772DF9}#4.1#0"; "BEAGETLISTENER.OCX"
Begin VB.Form frmBrowser 
   Caption         =   "University Transaction Sample"
   ClientHeight    =   7452
   ClientLeft      =   132
   ClientTop       =   708
   ClientWidth     =   10620
   LinkTopic       =   "Form1"
   ScaleHeight     =   7452
   ScaleWidth      =   10620
   StartUpPosition =   3  'Windows Default
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   1000
      Left            =   120
      Top             =   1080
   End
   Begin VB.CommandButton cmdRegisterForCourses 
      Caption         =   "Register for Courses"
      Height          =   492
      Left            =   7080
      TabIndex        =   15
      Top             =   1320
      Width           =   2172
   End
   Begin VB.TextBox txtRegisteredCourseCount 
      Height          =   288
      Left            =   2640
      Locked          =   -1  'True
      TabIndex        =   13
      Top             =   1080
      Width           =   1332
   End
   Begin VB.TextBox txtStudentID 
      Height          =   288
      Left            =   2640
      Locked          =   -1  'True
      TabIndex        =   12
      Top             =   600
      Width           =   1332
   End
   Begin VB.TextBox txtStudentName 
      Height          =   288
      Left            =   240
      Locked          =   -1  'True
      TabIndex        =   11
      Top             =   600
      Width           =   2052
   End
   Begin VB.CommandButton cmdGetRegisteredCourses 
      Caption         =   "Get Registered Courses"
      Height          =   492
      Left            =   7080
      TabIndex        =   10
      Top             =   600
      Width           =   2172
   End
   Begin BEAGetListener.GetListenerDlg dlgGetBootstrap 
      Left            =   240
      Top             =   1080
      _ExtentX        =   656
      _ExtentY        =   656
   End
   Begin VB.CommandButton cmdFind 
      Caption         =   "   Find Courses"
      Enabled         =   0   'False
      Height          =   612
      Left            =   3000
      TabIndex        =   8
      Top             =   1920
      Width           =   972
   End
   Begin VB.CommandButton cmdGetDetails 
      Caption         =   "   Get Details"
      Enabled         =   0   'False
      Height          =   1692
      Left            =   120
      TabIndex        =   7
      Top             =   2640
      Width           =   732
   End
   Begin VB.ListBox lstAvailable 
      Enabled         =   0   'False
      Height          =   1776
      Left            =   4320
      MultiSelect     =   2  'Extended
      Sorted          =   -1  'True
      TabIndex        =   6
      Top             =   480
      Width           =   2412
   End
   Begin ComctlLib.ListView lvDetails 
      Height          =   1692
      Left            =   960
      TabIndex        =   5
      Top             =   2640
      Width           =   9372
      _ExtentX        =   16531
      _ExtentY        =   2985
      View            =   3
      LabelEdit       =   1
      Sorted          =   -1  'True
      LabelWrap       =   -1  'True
      HideSelection   =   0   'False
      _Version        =   327682
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      Enabled         =   0   'False
      NumItems        =   0
   End
   Begin ComctlLib.StatusBar StatusBar1 
      Align           =   2  'Align Bottom
      Height          =   372
      Left            =   0
      TabIndex        =   4
      Top             =   7080
      Width           =   10620
      _ExtentX        =   18733
      _ExtentY        =   656
      Style           =   1
      SimpleText      =   ""
      _Version        =   327682
      BeginProperty Panels {0713E89E-850A-101B-AFC0-4210102A8DA7} 
         NumPanels       =   1
         BeginProperty Panel1 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Key             =   ""
            Object.Tag             =   ""
         EndProperty
      EndProperty
   End
   Begin RichTextLib.RichTextBox rtbDetails 
      Height          =   1932
      Left            =   6480
      TabIndex        =   2
      Top             =   4560
      Width           =   3852
      _ExtentX        =   6795
      _ExtentY        =   3408
      _Version        =   327681
      Enabled         =   0   'False
      ScrollBars      =   2
      TextRTF         =   $"frmBrowser.frx":0000
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   7.8
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
   End
   Begin VB.ComboBox cmbCriteria 
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.6
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   336
      Left            =   360
      TabIndex        =   1
      Top             =   2040
      Width           =   2415
   End
   Begin MSFlexGridLib.MSFlexGrid fgSchedule 
      Height          =   1932
      Left            =   240
      TabIndex        =   0
      Top             =   4560
      Width           =   6012
      _ExtentX        =   10605
      _ExtentY        =   3408
      _Version        =   65541
      Rows            =   19
      Cols            =   6
      ScrollTrack     =   -1  'True
      Enabled         =   -1  'True
      ScrollBars      =   0
      FormatString    =   "|^Monday|^Tuesday|^Wednesday|^Thursday|^Friday;|17:00|18:00|19:00|20:00|21:00|22:00|23:00"
   End
   Begin VB.Label Label3 
      Caption         =   "Registered Courses"
      Height          =   252
      Left            =   1080
      TabIndex        =   14
      Top             =   1080
      Width           =   1452
   End
   Begin VB.Label Label2 
      AutoSize        =   -1  'True
      Caption         =   "Selection Criteria"
      Height          =   192
      Left            =   360
      TabIndex        =   9
      Top             =   1800
      Width           =   1212
   End
   Begin VB.Label Label1 
      Alignment       =   2  'Center
      Caption         =   "Welcome to M3 University Course Registrar"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   18
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00800080&
      Height          =   492
      Left            =   240
      TabIndex        =   3
      Top             =   0
      Width           =   10212
   End
   Begin VB.Menu File 
      Caption         =   "&File"
      Begin VB.Menu Logon 
         Caption         =   "&Logon"
      End
      Begin VB.Menu Tracing 
         Caption         =   "&Tracing"
         Shortcut        =   ^T
      End
      Begin VB.Menu Exit 
         Caption         =   "E&xit"
      End
   End
   Begin VB.Menu Help 
      Caption         =   "&Help"
      Begin VB.Menu Using 
         Caption         =   "Using the sample brower"
      End
      Begin VB.Menu Separator1 
         Caption         =   "-"
      End
      Begin VB.Menu BEA 
         Caption         =   "BEA on the Web"
      End
      Begin VB.Menu Separator2 
         Caption         =   "-"
      End
      Begin VB.Menu About 
         Caption         =   "&About"
      End
   End
End
Attribute VB_Name = "frmBrowser"
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
' #ident       "@(#) Tests/Clients/UniversityT/frmBrowser.frm    $Revision: 1.1 $"

' frmBrowser.frm : UniversityT VB based Course Browser
Option Explicit

Private Declare Function ShellExecute Lib "shell32.dll" Alias _
    "ShellExecuteA" (ByVal hwnd As Long, ByVal lpOperation As _
    String, ByVal lpFile As String, ByVal lpParameters As String, _
    ByVal lpDirectory As String, ByVal nShowCmd As Long) As Long
Private Declare Function FindExecutable Lib "shell32.dll" Alias _
    "FindExecutableA" (ByVal lpFile As String, ByVal lpDirectory As _
    String, ByVal lpResult As String) As Long


'
' Define some color constants
'
Private Enum QBColors
    QBColorGreen = 2
    QBColorRed = 4
    QBColorWhite = 7
    QBColorLtGreen = 10
    QBColorLtRed = 12
    QBColorBrtWhite = 15
End Enum

Private mobjRegistrar As DIUniversityT_Registrar    ' The actual registrar object
Private mobjTransactionCurrent As DITobj_TransactionCurrent
Private mobjSynopsisEnum As DIUniversityT_CourseSynopsisEnumerator
Private mblnGotBootstrap As Boolean          ' Do we have the bootstrap object
Private Const RegistrarFactoryID = "IDL:beasys.com/UniversityT/RegistrarFactory:1.0"

Private mlngWaitTime As Long
Private mlngNumberLeft As Long
Private Const WindowLines As Long = 10
Private mintScheduleStartHour As Integer

Private mlngStudentID As Long


'
' Some collections for tracking things on the screen and
' caching information we've gotten from the server.
'
' mcolCourseDetails is the collection of CourseDetail objects
' we've gotten from the server.  It's key is the Cnnnnn where
' nnnnn is the course number.
'
Dim mcolCourseDetails As Collection
'
' The mcolConflicts collection is used to keep track of the
' time slots that have conflicts with the course that was
' most recently attempted to be added to the schedule.
' The elements are simply integers that have in the bottom
' eight bits, the column of the fgSchedule, and in the
' next eight bits, the row of the fgSchedule where a conflict
' has been shown, i.e., the background has been turned red.
Dim mcolConflicts As Collection
'
' The mcolScheduled collection is a collection of course numbers
' for each course that is in the schedule.  The key is Cnnnn.
'
Dim mcolScheduled As Collection
'
' The mcolRegistered collection is a collection of course
' numbers for each course that has been registered for the
' student.  The key is Cnnnn.
'
Dim mcolRegistered As Collection

'
' Sub item numbers in the details ListView
'
Enum itmCourseDetails
        itemNumber = 0      ' Not really a subitem
        itemTitle = 1
        itemProfessor = 2
        itemSchedule = 3
        itemCredits = 4
        itemCost = 5
        itemSeats = 6
End Enum

Private Function ScheduleToDescription(objClassSchedule As DIUniversityT_ClassSchedule) As String
    '
    ' This procedure takes a ClassSchedule object and produces
    ' a string of the form:
    '   10:30-12:00 MWF
    '
    Dim strDays As String
    Dim strStartHour As String
    Dim varStartTime As Variant
    Dim varEndTime As Variant
    
    With objClassSchedule
        If .class_days And 1 Then strDays = "M"
        If .class_days And 2 Then strDays = strDays + "Tu"
        If .class_days And 4 Then strDays = strDays + "W"
        If .class_days And 8 Then strDays = strDays + "Th"
        If .class_days And 16 Then strDays = strDays + "F"
        strStartHour = Format(.start_hour, "00")
        varStartTime = TimeValue(strStartHour + ":00")
        varEndTime = varStartTime + (.duration / 60) / 24
    End With
    ScheduleToDescription = Format(varStartTime, "hh:mm") + "-" _
                            + Format(varEndTime, "hh:mm") + " " _
                            + strDays
End Function
Private Sub AddToDetailsList(lngCourseNumber As Long, CourseTitle As String)
    '
    ' Add a course to the course details list.  Also check to see if
    ' there are details already available, and if so, populate
    ' entry with the details.
    '
    Dim strKey As String
    Dim Item As ListItem
    Dim objCourseDetail As DIUniversityT_CourseDetails
    strKey = CourseKey(lngCourseNumber)
    '
    ' See if the course is already in the details list
    '
    If InList(strKey, lvDetails.ListItems) Then
        Set Item = lvDetails.ListItems(strKey)
    Else
        '
        ' Course not already on the details list, so add
        '
        Set Item = lvDetails.ListItems.Add(, strKey, lngCourseNumber)
    End If
    
    '
    ' See if details available
    '
    If CourseInObjCol(lngCourseNumber, mcolCourseDetails) Then
        Set objCourseDetail = mcolCourseDetails.Item(strKey)
        Item.SubItems(itemTitle) = objCourseDetail.Title
        Item.SubItems(itemProfessor) = objCourseDetail.professor
        Item.SubItems(itemSchedule) = ScheduleToDescription(objCourseDetail.class_schedule)
        Item.SubItems(itemCredits) = Str(objCourseDetail.number_of_credits)
        Item.SubItems(itemCost) = Format(objCourseDetail.cost, "Currency")
        Item.SubItems(itemSeats) = Str(objCourseDetail.number_of_seats)
    Else
        Item.SubItems(itemTitle) = CourseTitle
        Item.SubItems(itemProfessor) = ""
        Item.SubItems(itemSchedule) = ""
        Item.SubItems(itemCredits) = ""
        Item.SubItems(itemCost) = ""
        Item.SubItems(itemSeats) = ""
    End If
End Sub
Private Sub GetCourseDetails()
    '
    ' This routine gets the course details for all the
    ' entries in the details list view that haven't already
    ' been gotten.
    '
    Dim strKey As String
    Dim Item As ListItem
    Dim DetailItem As ListItem
    Dim ItemEnum As Variant
    Dim aryCourseDetails As Variant
    Dim varCourseDetail As Variant
    Dim objCourseDetail As DIUniversityT_CourseDetails
    Dim aryCourseNumbers() As Long
    Dim colCourseNumbers As Collection
    Dim Index As Integer

    StatusBar1.SimpleText = "Getting course details"
    Set colCourseNumbers = New Collection
    For Each ItemEnum In lvDetails.ListItems
        If Not KeyInObjCol(ItemEnum.Key, mcolCourseDetails) Then
            '
            ' Don't have the course details yet, so add it to list
            '
            colCourseNumbers.Add Item:=Mid(ItemEnum.Key, 2, 10)
        End If
        varCourseDetail = Empty
    Next ItemEnum
    '
    ' Make sure there are some to get
    '
    If colCourseNumbers.Count < 1 Then
        StatusBar1.SimpleText = ""
        Exit Sub
    End If
    '
    ' Have a collection of course numbers to get the details
    ' on, now build an array from that collection
    '
    ReDim aryCourseNumbers(colCourseNumbers.Count - 1)
    Index = 0
    ItemEnum = Empty
    For Each ItemEnum In colCourseNumbers
        aryCourseNumbers(Index) = ItemEnum
        Index = Index + 1
    Next ItemEnum
    '
    ' Get the course details from the registrar
    '
    aryCourseDetails = mobjRegistrar.get_courses_details(aryCourseNumbers)
    '
    ' Now populate the course details collection
    '
    For Index = LBound(aryCourseDetails) To UBound(aryCourseDetails)
        Set objCourseDetail = aryCourseDetails(Index)
        strKey = CourseKey(objCourseDetail.course_number)
        If Not KeyInObjCol(strKey, mcolCourseDetails) Then
            mcolCourseDetails.Add Item:=objCourseDetail, Key:=strKey
        End If
        Call AddToDetailsList(objCourseDetail.course_number, objCourseDetail.Title)
    Next Index
    '
    ' Finally, get the selected course's details
    '
    'Set objCourseDetail = mcolCourseDetails.Item(strKey)
    StatusBar1.SimpleText = ""

End Sub


Private Sub About_Click()
    frmAbout.Show vbModal, Me
End Sub



Private Sub cmdGetDetails_Click()
    Call GetCourseDetails
End Sub

Private Sub cmdFind_Click()
    Dim varArraySynopsis As Variant
    Dim i As Long
    Dim SearchCriteria As String
    Dim exc As Variant       ' Exception return information
    
    StatusBar1.SimpleText = "Searching for courses"
    '
    ' Get a new set of synopsis when something entered here
    '
    lstAvailable.Clear     ' Remove existing list
    '
    ' See if the user specified "all" or "*"
    '
    If LCase(cmbCriteria) = "all" Or cmbCriteria = "*" Then
        SearchCriteria = ""
    Else
        SearchCriteria = cmbCriteria
    End If
    '
    ' Now get some the courses that match the criteria
    '
    varArraySynopsis = mobjRegistrar.get_courses_synopsis(SearchCriteria, 15, mlngNumberLeft, mobjSynopsisEnum, exc)
    ' Check for and handle any exceptions
    If (frmTracing.checkException(exc, "Getting list of courses", "get_course_synopsis", tvMedium)) Then
        If TypeOf exc Is DICORBASystemException Then
            MsgBox "CORBA System Exception occurred"
        Else
            MsgBox "Unknown exception occurred"
        End If
    Else
        For i = LBound(varArraySynopsis) To UBound(varArraySynopsis)
            lstAvailable.AddItem (varArraySynopsis(i).Title)
            lstAvailable.ItemData(lstAvailable.NewIndex) = varArraySynopsis(i).course_number
        Next i
    End If
    StatusBar1.SimpleText = ""
End Sub


Private Sub cmdGetRegisteredCourses_Click()
    Dim i As Integer
    Dim strKey As String
    Dim objCourseDetail As DIUniversityT_CourseDetails
    Dim lngCourseNumber As Long
    Dim objStudentDetails As DIUniversityT_StudentDetails
    Dim mRegisteredCourses As Variant
    Dim exc As Variant       ' Exception return information

    StatusBar1.SimpleText = "Getting registered courses"
    '
    ' Get the list of courses the student is registered to take
    '
    ' First update the student details
    Set objStudentDetails = mobjRegistrar.get_student_details(mlngStudentID, exc)
    If (frmTracing.checkException(exc, "Updating Student Details", "get_student_details", tvMedium)) Then
        If TypeOf exc Is DICORBASystemException Then
            MsgBox "CORBA System Exception occurred"
        Else
            MsgBox "Unknown exception occurred"
        End If
        MsgBox "Couldn't get student details"
        StatusBar1.SimpleText = ""
        Exit Sub
    End If
    
    txtStudentName.Text = objStudentDetails.Name
    txtStudentID.Text = Str(objStudentDetails.student_id)
    
    '
    ' Clear collection of registered courses
    '
    For i = mcolRegistered.Count To 1 Step -1     ' Go from last to first, faster
        mcolRegistered.Remove (i)
    Next i
    '
    ' Remove all the courses from the schedule
    '
    Call ClearCourseSchedule
    
    '
    ' Get up-to-date collection of courses
    '
    mRegisteredCourses = objStudentDetails.registered_courses
    txtRegisteredCourseCount.Text = UBound(mRegisteredCourses) - LBound(mRegisteredCourses) + 1
    
    '
    ' Add any new details to the details collection
    
    '
    ' Now add the courses to the collection of registered courses,
    ' the details collection and view, and the schedule
    '
    For i = LBound(mRegisteredCourses) To UBound(mRegisteredCourses)
        Set objCourseDetail = mRegisteredCourses(i)
        lngCourseNumber = objCourseDetail.course_number
        strKey = CourseKey(lngCourseNumber)
        If Not KeyInObjCol(strKey, mcolCourseDetails) Then
            mcolCourseDetails.Add Item:=objCourseDetail, Key:=strKey
        End If
        If Not KeyInCol(strKey, mcolRegistered) Then
            mcolRegistered.Add Item:=lngCourseNumber, Key:=strKey
        End If
        Call AddToDetailsList(lngCourseNumber, objCourseDetail.Title)
        Call AddClassToSchedule(lngCourseNumber, objCourseDetail.class_schedule, True)
    Next

    StatusBar1.SimpleText = ""

End Sub

Private Sub ClearCourseSchedule()
    '
    ' Delete everything in the schedule
    '
    Dim i As Integer
    Dim strKey As String
    Dim Item As ListItem
    Dim varCourseDetail As Variant
    Dim objCourseDetail As DIUniversityT_CourseDetails
    Dim objClassSchedule As DIUniversityT_ClassSchedule
    For i = mcolScheduled.Count To 1 Step -1
        strKey = CourseKey(mcolScheduled.Item(i))
        Set varCourseDetail = mcolCourseDetails.Item(strKey)
        Set objCourseDetail = varCourseDetail
        Set objClassSchedule = objCourseDetail.class_schedule
        Call RemoveClassFromSchedule(objCourseDetail.course_number, objClassSchedule)
        'mcolScheduled.Remove (i)
    Next i
End Sub

Private Sub cmdRegisterForCourses_Click()
    Dim NotRegisteredList As Variant
    Dim course As Variant
    Dim CourseList() As Long
    Dim i As Long
    Dim commit As Boolean
    Dim lngCourseNumber As Long
    Dim exc As Variant       ' Exception return information

    StatusBar1.SimpleText = "Registering for courses"
    '
    ' Take the courses that are currently in the schedule list and
    ' try to register for them.
    '
    If mcolScheduled.Count <= mcolRegistered.Count Then Exit Sub
    ReDim CourseList(mcolScheduled.Count - 1 - mcolRegistered.Count)
    i = 0
    For Each course In mcolScheduled
        lngCourseNumber = course
        If Not CourseInCol(lngCourseNumber, mcolRegistered) Then
            CourseList(i) = course
            i = i + 1
        End If
    Next course
    
    '
    ' Now try to register for the course, but first start a transaction
    '
    If beginTransaction() Then
        commit = True
        NotRegisteredList = mobjRegistrar.register_for_courses(mlngStudentID, CourseList, exc)
        If (frmTracing.checkException(exc, "Registering for courses", "register_for_courses", tvMedium)) Then
            If TypeOf exc Is DIUniversityT_TooManyCredits Then
                MsgBox "You are trying to register for too many credits"
            ElseIf TypeOf exc Is DICORBASystemException Then
                MsgBox "CORBA System Exception occurred"
            Else
                MsgBox "Unknown exception occurred"
            End If
            commit = False
        Else
            '
            ' See if all courses registered, if not ask if proceed anyway
            '
            If UBound(NotRegisteredList) >= LBound(NotRegisteredList) Then
                i = MsgBox("Register for others anyway?", vbOKCancel, "Not all courses registered")
                If i = vbCancel Then
                    commit = False
                End If
            End If
        End If
        If commit Then
            If commitTransaction(True) Then
                MsgBox "Successfully registered for courses"
                Call cmdGetRegisteredCourses_Click
            Else
                MsgBox "Transaction failed to commit"
            End If
        Else
            Call rollbackTransaction
        End If
    Else
        MsgBox "Couldn't begin transaction"
    End If
    StatusBar1.SimpleText = ""
End Sub

Private Sub Exit_Click()
    Call Logoff_Click
    End
End Sub

Private Sub Logon_Click()
    '
    ' User selected the open item on the File menu.
    ' Create the bootstrap object, display the form that
    '
    Dim objBootstrap As DITobj_Bootstrap                    ' Bootstrap object
    Dim objFactoryFinder As DITobj_FactoryFinder            ' Factory finder object
    Dim objRegisterFactory As DIUniversityT_RegistrarFactory ' Factory
    Dim objSecurityCurrent As DISecurityLevel2_Current
    Dim objPrincAuth As DITobj_PrincipalAuthenticator
    Dim objStudentDetails As DIUniversityT_StudentDetails
    Dim mRegisteredCourses As Variant
    Dim exc As Variant       ' Exception return information

    On Error Resume Next
    
    If mblnGotBootstrap = True Then
        frmTracing.Trace "Bootstrap Object already obtained" & vbCrLf, tvMedium
        Exit Sub
    Else
        frmTracing.Reset
    End If
    
    '
    ' Get the bootstrap object and logon
    '
    dlgGetBootstrap.ClientName = "VB Registrar"
    dlgGetBootstrap.lblUserName = "Student ID"
    If dlgGetBootstrap.Logon(objBootstrap, objSecurityCurrent, objPrincAuth) Then
        Logon.Enabled = False
    Else
        frmTracing.Trace "Error in logon", tvMedium
        Exit Sub
    End If

    mlngStudentID = dlgGetBootstrap.UserName
    '
    ' Get an object reference to a factory finder object
    '
    On Error Resume Next
    Set objFactoryFinder = objBootstrap.CreateObject("Tobj.FactoryFinder")
    If frmTracing.checkErr("Creating Factory Finder", tvMedium) = False Then
        MsgBox "Couldn't create factory finder"
        Exit Sub
    End If

    '
    ' Get a registrar factory object from the factory finder
    '
    Set objRegisterFactory = objFactoryFinder.find_one_factory_by_id(RegistrarFactoryID, exc)
    If frmTracing.checkException(exc, "Finding Registrar Factory", "find_one_factory_by_id", tvMedium) Then
        MsgBox "Couldn't find factory"
        Exit Sub
    End If
    
    '
    ' Have the Registrar factory create a new registrar object
    '
    Set mobjRegistrar = objRegisterFactory.find_registrar(exc)
    ' Check for and handle any exceptions
    If (frmTracing.checkException(exc, "Finding registrar", "find_registrar", tvMedium)) Then
        If TypeOf exc Is DICORBASystemException Then
            MsgBox "CORBA System Exception occurred"
        Else
            MsgBox "Unknown exception occurred"
        End If
        MsgBox "Couldn't find registrar"
        Exit Sub
    End If
    
    On Error Resume Next
    Set mobjTransactionCurrent = objBootstrap.CreateObject("Tobj.TransactionCurrent")
    If frmTracing.checkErr("Creating transaction current object", tvMedium) = False Then
        MsgBox "Couldn't create transaction current object"
        Exit Sub
    End If
    
    '
    ' Get the student details
    '
    Set objStudentDetails = mobjRegistrar.get_student_details(mlngStudentID, exc)
    If (frmTracing.checkException(exc, "Getting Student Details", "get_student_details", tvMedium)) Then
        If TypeOf exc Is DICORBASystemException Then
            MsgBox "CORBA System Exception occurred"
        Else
            MsgBox "Unknown exception occurred"
        End If
        MsgBox "Couldn't get student details"
        Exit Sub
    End If
    txtStudentName.Text = objStudentDetails.Name
    txtStudentID.Text = Str(objStudentDetails.student_id)
    mRegisteredCourses = objStudentDetails.registered_courses
    txtRegisteredCourseCount.Text = UBound(mRegisteredCourses) - LBound(mRegisteredCourses) + 1
    
    ' If everything created OK, proceed
    mblnGotBootstrap = True

    '
    ' Logged on, so disable the logon menu item and
    ' enable the other things
    '
    frmBrowser.Logon.Enabled = False
    frmBrowser.cmbCriteria.Enabled = True
    frmBrowser.cmdGetDetails.Enabled = True
    frmBrowser.cmdFind.Enabled = True
    frmBrowser.lstAvailable.Enabled = True
    frmBrowser.lvDetails.Enabled = True


End Sub
Private Sub lstAvailable_Scroll()
    Dim varArraySynopsis As Variant
    Dim i As Integer
    '
    ' Track the scroll bar to see if more items need to be
    ' obtained.
    '
    ' See if scrolled down to end of list
    '
    If (lstAvailable.TopIndex > (lstAvailable.ListCount - WindowLines - 1) _
            And mlngNumberLeft > 0) Then
        varArraySynopsis = mobjSynopsisEnum.get_next_n(15, mlngNumberLeft)
        For i = LBound(varArraySynopsis) To UBound(varArraySynopsis)
            lstAvailable.AddItem (varArraySynopsis(i).Title)
            lstAvailable.ItemData(lstAvailable.NewIndex) = varArraySynopsis(i).course_number
        Next i
    End If
    If mlngNumberLeft = 0 Then mobjSynopsisEnum.destroy
End Sub

Private Sub Form_Load()

    Call Logon_Click
    Set mcolCourseDetails = New Collection
    Set mcolConflicts = New Collection
    Set mcolScheduled = New Collection
    Set mcolRegistered = New Collection

    'Set up grid control
    Dim twips As Long
    
    fgSchedule.CellAlignment = flexAlignCenterCenter
    fgSchedule.ColWidth(0) = fgSchedule.ColWidth(0) + 60
    twips = fgSchedule.Width - fgSchedule.ColWidth(0) - 185
    fgSchedule.ColWidth(1) = twips / 5
    fgSchedule.ColWidth(2) = twips / 5
    fgSchedule.ColWidth(3) = twips / 5
    fgSchedule.ColWidth(4) = twips / 5
    fgSchedule.ColWidth(5) = twips / 5
    fgSchedule.Width = twips + fgSchedule.ColWidth(0) + 55
    fgSchedule.Col = 0
    fgSchedule.Row = 1
    mintScheduleStartHour = Val(fgSchedule.Text)
    
    'Set up Combo Box
    cmbCriteria.AddItem "Admin"
    cmbCriteria.AddItem "Computer"
    cmbCriteria.AddItem "Crime"
    cmbCriteria.AddItem "Law"
    cmbCriteria.AddItem "Math"
    cmbCriteria.Text = "*"
    
   
    'Set up Details listview
    With lvDetails.ColumnHeaders
        .Add Index:=itemNumber + 1, Text:="Number"
        .Item(itemNumber + 1).Width = lvDetails.Width * 8 / 100
        .Add Index:=itemTitle + 1, Text:="Title"
        .Item(itemTitle + 1).Width = lvDetails.Width * 20 / 100
        .Add Index:=itemProfessor + 1, Text:="Professor"
        .Item(itemProfessor + 1).Width = lvDetails.Width * 14 / 100
        .Add Index:=itemSchedule + 1, Text:="Schedule"
        .Item(itemSchedule + 1).Width = lvDetails.Width * 16 / 100
        .Add Index:=itemCredits + 1, Text:="Credits"
        .Item(itemCredits + 1).Width = lvDetails.Width * 5 / 100
        .Add Index:=itemCost + 1, Text:="Cost"
        .Item(itemCost + 1).Width = lvDetails.Width * 8 / 100
        .Add Index:=itemSeats + 1, Text:="Seats"
        .Item(itemSeats + 1).Width = lvDetails.Width * 5 / 100
    End With
End Sub



Private Sub lstAvailable_DblClick()
    Dim Index As Long
    Index = lstAvailable.ListIndex
    If Index >= 0 Then
        Call AddToDetailsList(lstAvailable.ItemData(Index), lstAvailable.List(Index))
    End If
End Sub

Private Sub lvDetails_dblclick()
    '
    ' Add a course to the the schedule
    '
    Dim strKey As String
    Dim Item As ListItem
    'Dim DetailItem As ListItem
    'Dim ItemEnum As Variant
    'Dim aryCourseDetails As Variant
    Dim varCourseDetail As Variant
    Dim objCourseDetail As DIUniversityT_CourseDetails
    Dim objClassSchedule As DIUniversityT_ClassSchedule
    'Dim aryCourseNumbers()
    'Dim colCourseNumbers As Collection
    Dim Index As Variant
    
    '
    ' Do all the click processing
    
    Call cmdGetDetails_Click
    
    '
    ' Get the course details and schedule of the course to add
    '
    Set Item = lvDetails.SelectedItem
    If Item Is Nothing Then Exit Sub
    strKey = Item.Key
    Set varCourseDetail = mcolCourseDetails.Item(strKey)
    Set objCourseDetail = varCourseDetail
    Set objClassSchedule = objCourseDetail.class_schedule
    
    '
    ' See if already scheduled
    '
    If KeyInCol(strKey, mcolScheduled) Then
        '
        ' Already scheduled, remove from the schedule, unless registered
        '
        If Not KeyInCol(strKey, mcolRegistered) Then
            Call RemoveClassFromSchedule(objCourseDetail.course_number, objClassSchedule)
        End If
    Else
        '
        ' Add to the schedule
        '
        Call AddClassToSchedule(objCourseDetail.course_number, objClassSchedule, False)
    End If
End Sub

Private Sub ClearConflicts()
    '
    ' This routine clears the red background from the
    ' conflicting spots
    '
    Dim i As Integer
    For i = mcolConflicts.Count To 1 Step -1
        fgSchedule.Col = mcolConflicts.Item(i) And 255
        fgSchedule.Row = mcolConflicts.Item(i) / 256
        fgSchedule.CellBackColor = QBColor(QBColorBrtWhite)
        mcolConflicts.Remove i
    Next i
    
End Sub
'
' Checks to see if there is a scheduling conflict
'
Private Function IsConflicting(lngCourseNumber As Long, _
                                Days As Collection, _
                                StartSlot As Integer, _
                                NumberOfSlots As Integer, _
                                Registered As Boolean) As Boolean
    Dim Day As Variant
    Dim TimeSlot As Variant
    Dim Conflict As Boolean
    Conflict = False
    Registered = False
    For Each Day In Days
        For TimeSlot = StartSlot To StartSlot + NumberOfSlots - 1
            fgSchedule.Col = Day
            fgSchedule.Row = TimeSlot
            If fgSchedule.Text <> "" Then
                If fgSchedule.Text <> Trim(Str(lngCourseNumber)) Then
                    Conflict = True
                    If CourseInCol(fgSchedule.Text, mcolRegistered) Then
                        Registered = True
                    End If
                End If
            End If
        Next TimeSlot
    Next Day
    IsConflicting = Conflict
End Function

'
' This routine "adds" a conflicting course to the
' schedule by turning the background of the conflicting
' schedule slots red and adds those cells to the
' conConflicts collection
'
Private Sub AddConflicting(lngCourseNumber As Long, _
                            Days As Collection, _
                            StartSlot As Integer, _
                            NumberOfSlots As Integer)
    Dim Day As Variant
    Dim TimeSlot As Integer
    For Each Day In Days
        For TimeSlot = StartSlot To StartSlot + NumberOfSlots - 1
            fgSchedule.Col = Day
            fgSchedule.Row = TimeSlot
            If fgSchedule.Text <> "" Then
                fgSchedule.CellBackColor = QBColor(QBColorLtRed)
                mcolConflicts.Add Day + TimeSlot * 256
            End If
        Next TimeSlot
    Next Day
End Sub

Private Sub RemoveClassFromSchedule(lngCourseNumber As Long, objClassSchedule As DIUniversityT_ClassSchedule)
    '
    ' Removes and existing scheduled course from the flex grid
    '
    Dim StartSlot As Integer
    Dim NumberOfSlots As Integer
    Dim TimeSlot As Integer
    Dim Day As Variant
    
    '
    ' Clear previous conflicts
    '
    If mcolConflicts.Count <> 0 Then Call ClearConflicts
    
    '
    ' Get a collection of days the class is being taught
    '
    Dim Days As New Collection
    With objClassSchedule
        If .class_days And 1 Then Days.Add (1)
        If .class_days And 2 Then Days.Add (2)
        If .class_days And 4 Then Days.Add (3)
        If .class_days And 8 Then Days.Add (4)
        If .class_days And 16 Then Days.Add (5)
        StartSlot = .start_hour - mintScheduleStartHour + 1
        NumberOfSlots = Int((.duration + 59) / 60)
    End With
    
    '
    ' Remove course number from flex grid
    '
    For Each Day In Days
        For TimeSlot = StartSlot To StartSlot + NumberOfSlots - 1
            fgSchedule.Col = Day
            fgSchedule.Row = TimeSlot
            fgSchedule.Text = ""
        Next TimeSlot
    Next Day
    '
    ' Remove course from collection of scheduled courses
    '
    mcolScheduled.Remove CourseKey(lngCourseNumber)

End Sub


Private Function CourseKey(lngCourseNumber As Long) As String
    '
    ' Turns a long into a key for collections of courses
    '
    CourseKey = "C" + Trim(Str(lngCourseNumber))
End Function

Private Function InList(strKey As String, List As ListItems) As Boolean
    '
    ' Returns true if key is in item list
    '
    Dim Var As Variant
    On Error Resume Next
        Var = List.Item(strKey)
    On Error GoTo 0
    If Var = Empty Then
        InList = False
    Else
        InList = True
    End If
End Function
Private Function KeyInCol(strKey As String, Col As Collection) As Boolean
    '
    ' Returns true if Key is an item in Col
    '
    Dim Var As Variant
    On Error Resume Next
        Var = Col.Item(strKey)
    On Error GoTo 0
    If Var = Empty Then
        KeyInCol = False
    Else
        KeyInCol = True
    End If
End Function
Private Function KeyInObjCol(strKey As String, Col As Collection) As Boolean
    '
    ' Returns true if Key is an item in Col
    '
    Dim Obj As Object
    On Error Resume Next
        Set Obj = Col.Item(strKey)
    On Error GoTo 0
    If Obj Is Nothing Then
        KeyInObjCol = False
    Else
        KeyInObjCol = True
    End If
End Function

Private Function CourseInCol(lngCourseNumber As Long, Col As Collection) As Boolean
    '
    ' Returns true if lngCourseNumber is a course in Col
    '
    Dim strKey As String
    strKey = CourseKey(lngCourseNumber)
    CourseInCol = KeyInCol(strKey, Col)
    
End Function

Private Function CourseInObjCol(lngCourseNumber As Long, Col As Collection) As Boolean
    '
    ' Returns true if lngCourseNumber is a course in Col
    '
    Dim strKey As String
    strKey = CourseKey(lngCourseNumber)
    CourseInObjCol = KeyInObjCol(strKey, Col)
    
End Function

Private Sub AddClassToSchedule(lngCourseNumber As Long, objClassSchedule As DIUniversityT_ClassSchedule, Registered)
    '
    ' Tries to add a class to the current schedule.
    ' If the course can be added without conflicting with a
    ' scheduled or registered course, it is added
    ' to the current schedule.  If there are conflicts with
    ' scheduled but not registered course, the conflicting segments
    ' are highlighted in red. If there is a conflict with
    ' a registered course, then a message is displayed indicating
    ' that the course conflicts with a registered course.
    '
    Dim StartSlot As Integer
    Dim NumberOfSlots As Integer
    Dim TimeSlot As Integer
    Dim Day As Variant
    Dim Conflict As Boolean
    Dim RegisteredConflict As Boolean
    
    '
    ' Clear previous conflicts
    '
    Call ClearConflicts
    
    '
    ' Get a collection of days the class is being taught
    '
    Dim Days As New Collection
    With objClassSchedule
        If .class_days And 1 Then Days.Add (1)
        If .class_days And 2 Then Days.Add (2)
        If .class_days And 4 Then Days.Add (3)
        If .class_days And 8 Then Days.Add (4)
        If .class_days And 16 Then Days.Add (5)
    
        StartSlot = .start_hour - mintScheduleStartHour + 1
        NumberOfSlots = Int((.duration + 59) / 60)
    End With
    
    '
    ' See if there is a conflict
    '
    If IsConflicting(lngCourseNumber, Days, StartSlot, NumberOfSlots, RegisteredConflict) Then
        '
        ' See if registered in the conflicting course
        '
        If RegisteredConflict Then
            '
            ' Simply display message box
            '
            MsgBox "Course conflicts with previously registered course"
        Else
            '
            ' Highlight the conflicts
            '
            Call AddConflicting(lngCourseNumber, Days, StartSlot, NumberOfSlots)
        End If
    Else
        '
        ' Add course number to flex grid
        '
        For Each Day In Days
            For TimeSlot = StartSlot To StartSlot + NumberOfSlots - 1
                fgSchedule.Col = Day
                fgSchedule.Row = TimeSlot
                fgSchedule.Text = Trim(Str(lngCourseNumber))
                If Registered Then
                    fgSchedule.CellBackColor = QBColor(QBColorLtGreen)
                Else
                    fgSchedule.CellBackColor = QBColor(QBColorBrtWhite)
                End If
            Next TimeSlot
        Next Day
        '
        ' Add course to collection of scheduled courses
        '
        mcolScheduled.Add lngCourseNumber, CourseKey(lngCourseNumber)
    End If
End Sub

Private Sub lvDetails_ColumnClick(ByVal ColumnHeader As ColumnHeader)
    '
    ' User wants to sort on this column
    '
    If (lvDetails.SortKey = ColumnHeader.Index - 1) Then
        ' user clicked the already sorted column, switch the order of the sort
        If lvDetails.SortOrder = lvwAscending Then
            lvDetails.SortOrder = lvwDescending
        Else
            lvDetails.SortOrder = lvwAscending
        End If
    Else
        lvDetails.SortKey = ColumnHeader.Index - 1
    End If
End Sub


Private Sub lvDetails_Click()
    '
    ' Display the course details, i.e., description of the selected course
    '
    Dim strKey As String
    Dim Item As ListItem
    Dim objCourseDetail As DIUniversityT_CourseDetails
    
    Set Item = lvDetails.SelectedItem
    If Item Is Nothing Then Exit Sub
    strKey = Item.Key
    '
    ' First, get any details for courses that haven't yet been obtained
    '
    Call GetCourseDetails
    '
    ' See if the details have been obtained yet
    '
    Set objCourseDetail = mcolCourseDetails.Item(strKey)
    rtbDetails.Text = objCourseDetail.Description
    
End Sub

Private Sub Timer1_Timer()
    mlngWaitTime = mlngWaitTime - 1
End Sub

Private Sub Tracing_Click()
    If (Tracing.Checked) Then
        '
        ' Hide tracing window and uncheck tracing
        '
        frmTracing.Visible = False
        Tracing.Checked = False
    Else
        '
        ' Display tracing window and check tracing
        '
        frmTracing.Visible = True
        Tracing.Checked = True
    End If

End Sub


Private Sub Logoff_Click()
    '
    ' Clean up and return things to the way they began
    '
    Logon.Enabled = True
    'Logoff.Enabled = False
    cmbCriteria.Enabled = False
    cmdGetDetails.Enabled = False
    cmdFind.Enabled = False
    lstAvailable.Enabled = False
    lvDetails.Enabled = False
    
    mblnGotBootstrap = False
    Set mobjRegistrar = Nothing

End Sub


Private Function beginTransaction() As Boolean
    '
    ' Start a transaction and check for errors
    '
    Dim exc As Variant
    Call mobjTransactionCurrent.begin(exc)
    If (frmTracing.checkErr("Start transaction", tvHigh)) = False Then
        MsgBox "Couldn't start transaction"
        beginTransaction = False
    Else
        beginTransaction = True
    End If
End Function


Private Function commitTransaction(report As Boolean) As Boolean
    '
    ' Start a transaction and check for errors
    '
    Dim exc As Variant
    Call mobjTransactionCurrent.commit(report, exc)
    If (frmTracing.checkErr("Commit transaction", tvHigh)) = False Then
        MsgBox "Couldn't commit transaction"
        commitTransaction = False
    Else
        commitTransaction = True
    End If
End Function

Private Function rollbackTransaction() As Boolean
    '
    ' Rollback a previously started transaction
    '
    Dim exc As Variant
    StatusBar1.SimpleText = "Rolling back transaction"

    Call mobjTransactionCurrent.rollback(exc)
    If (frmTracing.checkErr("Rollback transaction", tvHigh)) = False Then
        MsgBox "Couldn't rollback transaction"
        rollbackTransaction = False
    Else
        rollbackTransaction = True
    End If
    '
    ' Need to wait 3 seconds as rollback is asynchronous
    '
    mlngWaitTime = 3
    Timer1.Interval = 1000
    Me.MousePointer = vbHourglass
    Timer1.Enabled = True
    While mlngWaitTime > 0
        DoEvents
    Wend
    Timer1.Enabled = False
    Me.MousePointer = vbDefault
    StatusBar1.SimpleText = ""

End Function

Private Sub BEA_Click()
    Dim FileName, Dummy As String
    Dim BrowserExec As String * 255
    Dim RetVal As Long
    Dim FileNumber As Integer
    ' First, create a known, temporary HTML file
    BrowserExec = Space(255)
    FileName = "temphtm.html"
    FileNumber = FreeFile                    ' Get unused file number
    Open FileName For Output As #FileNumber  ' Create temp HTML file
        Write #FileNumber, "<HTML> <\HTML>"  ' Output text
    Close #FileNumber                        ' Close file
    ' Then find the application associated with it
    RetVal = FindExecutable(FileName, Dummy, BrowserExec)
    Kill FileName                   ' delete temp HTML file
    BrowserExec = Trim(BrowserExec)
    ' If an application is found, launch it!
    If RetVal <= 32 Or IsEmpty(BrowserExec) Then ' Error
    Else
        RetVal = ShellExecute(Me.hwnd, "open", BrowserExec, _
          "www.beasys.com", Dummy, 1)
        If RetVal <= 32 Then        ' Error
            MsgBox "Web Page not Opened", vbExclamation, "URL Failed"
        End If
    End If

End Sub


