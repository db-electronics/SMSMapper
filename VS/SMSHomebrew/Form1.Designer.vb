<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Form1
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(Form1))
        Me.ButtonDetectSerialPort = New System.Windows.Forms.Button()
        Me.ComboBoxSerialPorts = New System.Windows.Forms.ComboBox()
        Me.MenuStrip1 = New System.Windows.Forms.MenuStrip()
        Me.FileToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.OpenROMToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ListBoxROM = New System.Windows.Forms.ListBox()
        Me.LabelROMHeader = New System.Windows.Forms.Label()
        Me.LabelFileName = New System.Windows.Forms.Label()
        Me.ListBox1 = New System.Windows.Forms.ListBox()
        Me.ButtonJumpROM = New System.Windows.Forms.Button()
        Me.TextBoxJumpTo = New System.Windows.Forms.TextBox()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.TextBoxCalcChecksum = New System.Windows.Forms.TextBox()
        Me.TextBoxROMChecksum = New System.Windows.Forms.TextBox()
        Me.TabControl1 = New System.Windows.Forms.TabControl()
        Me.TabPage1 = New System.Windows.Forms.TabPage()
        Me.TabPage2 = New System.Windows.Forms.TabPage()
        Me.LabelBurnerStatus = New System.Windows.Forms.Label()
        Me.ProgressBarMain = New System.Windows.Forms.ProgressBar()
        Me.PictureBox1 = New System.Windows.Forms.PictureBox()
        Me.ButtonReloadROM = New System.Windows.Forms.Button()
        Me.MenuStrip1.SuspendLayout()
        Me.TabControl1.SuspendLayout()
        Me.TabPage1.SuspendLayout()
        Me.TabPage2.SuspendLayout()
        CType(Me.PictureBox1, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'ButtonDetectSerialPort
        '
        Me.ButtonDetectSerialPort.Location = New System.Drawing.Point(6, 10)
        Me.ButtonDetectSerialPort.Name = "ButtonDetectSerialPort"
        Me.ButtonDetectSerialPort.Size = New System.Drawing.Size(75, 23)
        Me.ButtonDetectSerialPort.TabIndex = 0
        Me.ButtonDetectSerialPort.Text = "Detect Ports"
        Me.ButtonDetectSerialPort.UseVisualStyleBackColor = True
        '
        'ComboBoxSerialPorts
        '
        Me.ComboBoxSerialPorts.FormattingEnabled = True
        Me.ComboBoxSerialPorts.Location = New System.Drawing.Point(87, 10)
        Me.ComboBoxSerialPorts.Name = "ComboBoxSerialPorts"
        Me.ComboBoxSerialPorts.Size = New System.Drawing.Size(121, 21)
        Me.ComboBoxSerialPorts.TabIndex = 1
        '
        'MenuStrip1
        '
        Me.MenuStrip1.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.FileToolStripMenuItem})
        Me.MenuStrip1.Location = New System.Drawing.Point(0, 0)
        Me.MenuStrip1.Name = "MenuStrip1"
        Me.MenuStrip1.Size = New System.Drawing.Size(911, 24)
        Me.MenuStrip1.TabIndex = 3
        Me.MenuStrip1.Text = "MenuStrip1"
        '
        'FileToolStripMenuItem
        '
        Me.FileToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.OpenROMToolStripMenuItem})
        Me.FileToolStripMenuItem.Name = "FileToolStripMenuItem"
        Me.FileToolStripMenuItem.Size = New System.Drawing.Size(37, 20)
        Me.FileToolStripMenuItem.Text = "File"
        '
        'OpenROMToolStripMenuItem
        '
        Me.OpenROMToolStripMenuItem.Name = "OpenROMToolStripMenuItem"
        Me.OpenROMToolStripMenuItem.Size = New System.Drawing.Size(133, 22)
        Me.OpenROMToolStripMenuItem.Text = "Open ROM"
        '
        'ListBoxROM
        '
        Me.ListBoxROM.Font = New System.Drawing.Font("Lucida Console", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.ListBoxROM.FormattingEnabled = True
        Me.ListBoxROM.Location = New System.Drawing.Point(9, 92)
        Me.ListBoxROM.Name = "ListBoxROM"
        Me.ListBoxROM.ScrollAlwaysVisible = True
        Me.ListBoxROM.Size = New System.Drawing.Size(500, 381)
        Me.ListBoxROM.TabIndex = 4
        '
        'LabelROMHeader
        '
        Me.LabelROMHeader.AutoSize = True
        Me.LabelROMHeader.Location = New System.Drawing.Point(10, 476)
        Me.LabelROMHeader.Name = "LabelROMHeader"
        Me.LabelROMHeader.Size = New System.Drawing.Size(39, 13)
        Me.LabelROMHeader.TabIndex = 5
        Me.LabelROMHeader.Text = "Label1"
        '
        'LabelFileName
        '
        Me.LabelFileName.AutoSize = True
        Me.LabelFileName.Location = New System.Drawing.Point(9, 60)
        Me.LabelFileName.Name = "LabelFileName"
        Me.LabelFileName.Size = New System.Drawing.Size(39, 13)
        Me.LabelFileName.TabIndex = 6
        Me.LabelFileName.Text = "Label1"
        '
        'ListBox1
        '
        Me.ListBox1.Font = New System.Drawing.Font("Lucida Console", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.ListBox1.FormattingEnabled = True
        Me.ListBox1.Items.AddRange(New Object() {"Offset(h)  00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F"})
        Me.ListBox1.Location = New System.Drawing.Point(9, 76)
        Me.ListBox1.Name = "ListBox1"
        Me.ListBox1.Size = New System.Drawing.Size(500, 17)
        Me.ListBox1.TabIndex = 7
        '
        'ButtonJumpROM
        '
        Me.ButtonJumpROM.Location = New System.Drawing.Point(6, 6)
        Me.ButtonJumpROM.Name = "ButtonJumpROM"
        Me.ButtonJumpROM.Size = New System.Drawing.Size(75, 23)
        Me.ButtonJumpROM.TabIndex = 8
        Me.ButtonJumpROM.Text = "Jump To"
        Me.ButtonJumpROM.UseVisualStyleBackColor = True
        '
        'TextBoxJumpTo
        '
        Me.TextBoxJumpTo.Location = New System.Drawing.Point(87, 8)
        Me.TextBoxJumpTo.Name = "TextBoxJumpTo"
        Me.TextBoxJumpTo.Size = New System.Drawing.Size(75, 20)
        Me.TextBoxJumpTo.TabIndex = 9
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Location = New System.Drawing.Point(570, 455)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(85, 13)
        Me.Label1.TabIndex = 10
        Me.Label1.Text = "ROM Checksum"
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Location = New System.Drawing.Point(574, 431)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(81, 13)
        Me.Label2.TabIndex = 11
        Me.Label2.Text = "Calc Checksum"
        '
        'TextBoxCalcChecksum
        '
        Me.TextBoxCalcChecksum.Font = New System.Drawing.Font("Lucida Console", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.TextBoxCalcChecksum.Location = New System.Drawing.Point(518, 429)
        Me.TextBoxCalcChecksum.Name = "TextBoxCalcChecksum"
        Me.TextBoxCalcChecksum.ReadOnly = True
        Me.TextBoxCalcChecksum.Size = New System.Drawing.Size(46, 20)
        Me.TextBoxCalcChecksum.TabIndex = 12
        Me.TextBoxCalcChecksum.Text = "$XXXX"
        '
        'TextBoxROMChecksum
        '
        Me.TextBoxROMChecksum.Font = New System.Drawing.Font("Lucida Console", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.TextBoxROMChecksum.Location = New System.Drawing.Point(518, 453)
        Me.TextBoxROMChecksum.Name = "TextBoxROMChecksum"
        Me.TextBoxROMChecksum.ReadOnly = True
        Me.TextBoxROMChecksum.Size = New System.Drawing.Size(46, 20)
        Me.TextBoxROMChecksum.TabIndex = 13
        Me.TextBoxROMChecksum.Text = "$XXXX"
        '
        'TabControl1
        '
        Me.TabControl1.Controls.Add(Me.TabPage1)
        Me.TabControl1.Controls.Add(Me.TabPage2)
        Me.TabControl1.Location = New System.Drawing.Point(520, 60)
        Me.TabControl1.Name = "TabControl1"
        Me.TabControl1.SelectedIndex = 0
        Me.TabControl1.Size = New System.Drawing.Size(379, 288)
        Me.TabControl1.TabIndex = 14
        '
        'TabPage1
        '
        Me.TabPage1.BackColor = System.Drawing.Color.WhiteSmoke
        Me.TabPage1.Controls.Add(Me.LabelBurnerStatus)
        Me.TabPage1.Controls.Add(Me.ButtonDetectSerialPort)
        Me.TabPage1.Controls.Add(Me.ComboBoxSerialPorts)
        Me.TabPage1.Location = New System.Drawing.Point(4, 22)
        Me.TabPage1.Name = "TabPage1"
        Me.TabPage1.Padding = New System.Windows.Forms.Padding(3)
        Me.TabPage1.Size = New System.Drawing.Size(371, 262)
        Me.TabPage1.TabIndex = 0
        Me.TabPage1.Text = "Burner"
        '
        'TabPage2
        '
        Me.TabPage2.BackColor = System.Drawing.Color.WhiteSmoke
        Me.TabPage2.Controls.Add(Me.ButtonJumpROM)
        Me.TabPage2.Controls.Add(Me.TextBoxJumpTo)
        Me.TabPage2.Location = New System.Drawing.Point(4, 22)
        Me.TabPage2.Name = "TabPage2"
        Me.TabPage2.Padding = New System.Windows.Forms.Padding(3)
        Me.TabPage2.Size = New System.Drawing.Size(371, 262)
        Me.TabPage2.TabIndex = 1
        Me.TabPage2.Text = "ROM"
        '
        'LabelBurnerStatus
        '
        Me.LabelBurnerStatus.AutoSize = True
        Me.LabelBurnerStatus.Location = New System.Drawing.Point(214, 15)
        Me.LabelBurnerStatus.Name = "LabelBurnerStatus"
        Me.LabelBurnerStatus.Size = New System.Drawing.Size(105, 13)
        Me.LabelBurnerStatus.TabIndex = 2
        Me.LabelBurnerStatus.Text = "Burner Not Detected"
        '
        'ProgressBarMain
        '
        Me.ProgressBarMain.Location = New System.Drawing.Point(12, 492)
        Me.ProgressBarMain.Name = "ProgressBarMain"
        Me.ProgressBarMain.Size = New System.Drawing.Size(887, 23)
        Me.ProgressBarMain.TabIndex = 15
        '
        'PictureBox1
        '
        Me.PictureBox1.Image = Global.SMSHomebrew.My.Resources.Resources.db_billboard_no_text
        Me.PictureBox1.Location = New System.Drawing.Point(773, 27)
        Me.PictureBox1.Name = "PictureBox1"
        Me.PictureBox1.Size = New System.Drawing.Size(122, 49)
        Me.PictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage
        Me.PictureBox1.TabIndex = 16
        Me.PictureBox1.TabStop = False
        '
        'ButtonReloadROM
        '
        Me.ButtonReloadROM.Location = New System.Drawing.Point(433, 49)
        Me.ButtonReloadROM.Name = "ButtonReloadROM"
        Me.ButtonReloadROM.Size = New System.Drawing.Size(75, 23)
        Me.ButtonReloadROM.TabIndex = 17
        Me.ButtonReloadROM.Text = "Reload ROM"
        Me.ButtonReloadROM.UseVisualStyleBackColor = True
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(911, 527)
        Me.Controls.Add(Me.ButtonReloadROM)
        Me.Controls.Add(Me.PictureBox1)
        Me.Controls.Add(Me.ProgressBarMain)
        Me.Controls.Add(Me.TabControl1)
        Me.Controls.Add(Me.TextBoxROMChecksum)
        Me.Controls.Add(Me.TextBoxCalcChecksum)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.Label1)
        Me.Controls.Add(Me.ListBox1)
        Me.Controls.Add(Me.LabelFileName)
        Me.Controls.Add(Me.LabelROMHeader)
        Me.Controls.Add(Me.ListBoxROM)
        Me.Controls.Add(Me.MenuStrip1)
        Me.Icon = CType(resources.GetObject("$this.Icon"), System.Drawing.Icon)
        Me.MainMenuStrip = Me.MenuStrip1
        Me.MaximizeBox = False
        Me.Name = "Form1"
        Me.Text = "db SMS Homebrew Interface"
        Me.MenuStrip1.ResumeLayout(False)
        Me.MenuStrip1.PerformLayout()
        Me.TabControl1.ResumeLayout(False)
        Me.TabPage1.ResumeLayout(False)
        Me.TabPage1.PerformLayout()
        Me.TabPage2.ResumeLayout(False)
        Me.TabPage2.PerformLayout()
        CType(Me.PictureBox1, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents ButtonDetectSerialPort As System.Windows.Forms.Button
    Friend WithEvents ComboBoxSerialPorts As System.Windows.Forms.ComboBox
    Friend WithEvents MenuStrip1 As System.Windows.Forms.MenuStrip
    Friend WithEvents FileToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents OpenROMToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents ListBoxROM As System.Windows.Forms.ListBox
    Friend WithEvents LabelROMHeader As System.Windows.Forms.Label
    Friend WithEvents LabelFileName As System.Windows.Forms.Label
    Friend WithEvents ListBox1 As System.Windows.Forms.ListBox
    Friend WithEvents ButtonJumpROM As System.Windows.Forms.Button
    Friend WithEvents TextBoxJumpTo As System.Windows.Forms.TextBox
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents TextBoxCalcChecksum As System.Windows.Forms.TextBox
    Friend WithEvents TextBoxROMChecksum As System.Windows.Forms.TextBox
    Friend WithEvents TabControl1 As System.Windows.Forms.TabControl
    Friend WithEvents TabPage1 As System.Windows.Forms.TabPage
    Friend WithEvents TabPage2 As System.Windows.Forms.TabPage
    Friend WithEvents LabelBurnerStatus As System.Windows.Forms.Label
    Friend WithEvents ProgressBarMain As System.Windows.Forms.ProgressBar
    Friend WithEvents PictureBox1 As System.Windows.Forms.PictureBox
    Friend WithEvents ButtonReloadROM As System.Windows.Forms.Button

End Class
