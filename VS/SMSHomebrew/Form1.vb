'//*************************************************************
'//
'//  $Rev:: 342                                            $:  Revision of last commit
'//  $Author:: reneleonrichard                             $:  Author of last commit
'//  $Date:: 2014-11-12 17:01:20 -0500 (Wed, 12 Nov 2014)  $:  Date of last commit
'//  $HeadURL: https://subversion.assembla.com/svn/db_repository/trunk/Personal%20Projects/SMSHomebrew/Software/SMSHomebrew/Form1.vb $
'//
'//*************************************************************
'// Copyright René Richard 2014
'//*************************************************************

Imports System
Imports System.IO
Imports System.Text
Imports System.IO.Ports

Public Class Form1

    Dim intHeaderOffset As Integer
    Dim intLoadedROMSize As Integer

    Private u16ROMHeaderAddress() As UShort = {&H1FF0, &H3FF0, &H7FF0}

    Dim ROMLoad As Byte

    Private Sub ButtonDetectSerialPort_Click(sender As Object, e As EventArgs) Handles ButtonDetectSerialPort.Click
        On Error GoTo ErrorHandler

        Dim strPorts As String() = SerialPort.GetPortNames

        ComboBoxSerialPorts.Items.Clear()
        ComboBoxSerialPorts.Items.AddRange(strPorts)
        ComboBoxSerialPorts.SelectedIndex = 0

        Exit Sub
ErrorHandler:
        MsgBox("Error: " & Err.Description & vbNewLine & "Error level: " & Err.Erl.ToString)
    End Sub

    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        ListBoxROM.Items.Clear()
        LabelROMHeader.Text = ""
        LabelFileName.Text = ""
        ButtonReloadROM.Enabled = False
        intHeaderOffset = 0
        Call ButtonDetectSerialPort_Click(Nothing, Nothing)
    End Sub

    Private Sub OpenROMToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles OpenROMToolStripMenuItem.Click

        On Error GoTo ErrorHandler

        'prepare a file open dialog to browse to the database
        Dim fd As OpenFileDialog = New OpenFileDialog()
        fd.Title = "Select ROM"
        fd.InitialDirectory = My.Settings.PreviousDirectory
        fd.Filter = "SMS ROM (*.sms;*.bin)|*.sms;*.bin|" + _
                    "All files (*.*)|*.*"
        fd.RestoreDirectory = True

        'Else config.xml does exist, in this case allow user to select a different database (a backup perhaps?)
        If fd.ShowDialog() = DialogResult.OK Then
            'remember this directory for next time
            My.Settings.CurrentROM = fd.FileName
            My.Settings.PreviousDirectory = Path.GetDirectoryName(fd.FileName)
        Else
            'exit if user clicked cancel
            Exit Sub
        End If

        LoadROM(My.Settings.CurrentROM)
        ButtonReloadROM.Enabled = True

        Exit Sub
Errorhandler:
        MsgBox("Error: " & Err.Description)
    End Sub

    Private Sub ButtonJumpROM_Click(sender As Object, e As EventArgs) Handles ButtonJumpROM.Click
        If IsHex(TextBoxJumpTo.Text) Then
            Dim intOffset As Integer = Convert.ToInt32(TextBoxJumpTo.Text, 16)
            If intOffset >= intLoadedROMSize Then
                MessageBox.Show("Offset is greater than ROM size")
                Exit Sub
            End If
            intOffset = intOffset / 16
            ListBoxROM.SelectedIndex = intOffset
        Else
            MessageBox.Show("Please enter a hexadecimal offset")
        End If
    End Sub

    Private Sub TextBoxJumpTo_KeyDown(sender As Object, e As KeyEventArgs) Handles TextBoxJumpTo.KeyDown
        If e.KeyCode = Keys.Enter Then
            e.SuppressKeyPress = True
            Call ButtonJumpROM_Click(Nothing, Nothing)
        End If
    End Sub

    Private Function IsHex(ByVal str As String) As Boolean
        Try
            Dim num As Long = CLng("&H" & str)
            Return True
        Catch ex As Exception
            Return False
        End Try
    End Function

    Private Sub LoadROM(strPath As String)

        On Error GoTo Errorhandler

        'load the file
        Using binReader As New BinaryReader(File.Open(My.Settings.CurrentROM, FileMode.Open))

            Dim strbLine As New StringBuilder
            Dim intLinePos As Integer = 0
            Dim intFilePos As Integer = 0
            Dim intLength As Integer = binReader.BaseStream.Length
            Dim boolFoundHeader As Boolean = False

            'read rom header
            binReader.BaseStream.Position = &H7FF0
            Dim strTMR As String = binReader.ReadChars(8)
            'if TMR SEGA not found at $7FF0, it probably is $200 bytes further
            If strTMR <> "TMR SEGA" Then
                binReader.BaseStream.Position = &H7FF0 + &H200
                strTMR = binReader.ReadChars(8)
                If strTMR <> "TMR SEGA" Then
                    MessageBox.Show("Warning: TMR SEGA not found in ROM file")
                Else
                    intHeaderOffset = &H200
                    intFilePos = intHeaderOffset
                    intLoadedROMSize = intLength
                End If
                'display file name and real ROM size
                LabelFileName.Text = Path.GetFileName(My.Settings.CurrentROM) & " : " & (intLength - 512).ToString & " bytes " & _
                                    "+ 512 Byte Header"
                intLoadedROMSize = intLength - 512
            Else
                'display file name and real ROM size
                intHeaderOffset = 0
                intLoadedROMSize = intLength
                LabelFileName.Text = Path.GetFileName(My.Settings.CurrentROM) & " : " & intLength.ToString & " bytes"
            End If
            'skip 2 bytes, read checksum and rest of header
            binReader.BaseStream.Position = &H7FFA + intHeaderOffset
            Dim u16Checksum As UShort = binReader.ReadUInt16
            Dim bytesHeader() As Byte = binReader.ReadBytes(4)

            'decode header values, as per http://www.smspower.org/Development/ROMHeader
            Dim u32Version As UInteger = bytesHeader(2) And &HF
            Dim u32RegionCode As UInteger = (bytesHeader(3) And &HF0) >> 4
            Dim u32ROMSize As UInteger = bytesHeader(3) And &HF

            'convert region code
            Dim strRegionCode As String
            Select Case u32RegionCode
                Case 3
                    strRegionCode = "SMS Japan"
                Case 4
                    strRegionCode = "SMS Export"
                Case 5
                    strRegionCode = "GG Japan"
                Case 5
                    strRegionCode = "GG Export"
                Case 6
                    strRegionCode = "GG International"
                Case Else
                    strRegionCode = "Unknown"
            End Select

            Dim strROMSize As String
            Dim intChecksumRange As Integer
            Select Case u32ROMSize
                Case &HA
                    strROMSize = "8KB"
                    intChecksumRange = 8192
                Case &HB
                    strROMSize = "16KB"
                    intChecksumRange = 16384
                Case &HC
                    strROMSize = "32KB"
                    intChecksumRange = 32768
                Case &HD
                    strROMSize = "48KB"
                    intChecksumRange = 32768
                Case &HE
                    strROMSize = "64KB"
                    intChecksumRange = 65536
                Case &HF
                    strROMSize = "128KB"
                    intChecksumRange = 131072
                Case &H0
                    strROMSize = "256KB"
                    intChecksumRange = 262144
                Case &H1
                    strROMSize = "512KB"
                    intChecksumRange = 524288
                Case &H2
                    strROMSize = "1MB"
                    intChecksumRange = 1048576
                Case Else
                    strROMSize = "Unknown"
            End Select

            'calculate checksum of ROM
            binReader.BaseStream.Position = 0 + intHeaderOffset
            Dim u64ChecksumCalc As ULong
            While (intFilePos - intHeaderOffset) < &H7FF0
                u64ChecksumCalc += binReader.ReadByte
                intFilePos += 1
            End While
            'skip over header
            intFilePos += 16
            binReader.BaseStream.Position = intFilePos
            While intFilePos < (intChecksumRange + intHeaderOffset)
                u64ChecksumCalc += binReader.ReadByte
                intFilePos += 1
            End While
            Dim u16ChecksumCalc As UShort = Convert.ToUInt16(u64ChecksumCalc And &HFFFF)
            'display checksum results
            TextBoxCalcChecksum.Text = "$" & u16ChecksumCalc.ToString("X4")
            TextBoxROMChecksum.Text = "$" & u16Checksum.ToString("X4")

            'display ROM Header information 
            LabelROMHeader.Text = "@$7FF0 : " & strTMR & " : " & _
                                        "Checksum " & u16Checksum.ToString("X4") & " : " & _
                                        "Version " & u32Version.ToString & " : " & _
                                        "Region " & strRegionCode & " : " & _
                                        "Size " & strROMSize

            'return to beginning of file, load ROM into listbox
            binReader.BaseStream.Position = 0 + intHeaderOffset
            ListBoxROM.Items.Clear()
            strbLine.Clear()
            intFilePos = intHeaderOffset
            While intFilePos < intLength
                'display offset at the beginning of every line
                strbLine.Append(" " & (intFilePos - intHeaderOffset).ToString("X8") & " ")
                While intLinePos < 16
                    'display 16 hex values per line
                    strbLine.Append(" " & binReader.ReadByte.ToString("X2"))
                    intLinePos += 1
                End While
                strbLine.AppendLine()
                ListBoxROM.Items.Add(strbLine)
                strbLine.Clear()
                intFilePos += 16
                intLinePos = 0
                Application.DoEvents()
            End While
        End Using

        Exit Sub
Errorhandler:
        MsgBox("Error: " & Err.Description)
    End Sub

    Private Sub ButtonReloadROM_Click(sender As Object, e As EventArgs) Handles ButtonReloadROM.Click

        LoadROM(My.Settings.CurrentROM)

    End Sub
End Class
