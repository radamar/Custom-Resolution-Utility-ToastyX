object DetailedResolutionForm: TDetailedResolutionForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Detailed Resolution'
  ClientHeight = 389
  ClientWidth = 381
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Timing: TLabel
    Left = 8
    Top = 12
    Width = 34
    Height = 13
    Caption = 'Timing:'
  end
  object TimingComboBox: TComboBox
    Left = 46
    Top = 8
    Width = 195
    Height = 21
    Style = csDropDownList
    ItemHeight = 0
    TabOrder = 0
    OnChange = TimingComboBoxChange
  end
  object TimingCopyButton: TButton
    Left = 248
    Top = 8
    Width = 42
    Height = 21
    Caption = 'Copy'
    TabOrder = 1
    OnClick = TimingCopyButtonClick
  end
  object TimingPasteButton: TButton
    Left = 290
    Top = 8
    Width = 42
    Height = 21
    Caption = 'Paste'
    TabOrder = 2
    OnClick = TimingPasteButtonClick
  end
  object TimingResetButton: TButton
    Left = 332
    Top = 8
    Width = 42
    Height = 21
    Caption = 'Reset'
    TabOrder = 3
    OnClick = TimingResetButtonClick
  end
  object ParametersGroupBox: TGroupBox
    Left = 8
    Top = 35
    Width = 365
    Height = 213
    Caption = ' Parameters '
    ParentBackground = False
    TabOrder = 4
    object Active: TLabel
      Left = 25
      Top = 35
      Width = 34
      Height = 13
      Caption = 'Active:'
    end
    object Front: TLabel
      Left = 25
      Top = 60
      Width = 60
      Height = 13
      Caption = 'Front porch:'
    end
    object Sync: TLabel
      Left = 25
      Top = 85
      Width = 56
      Height = 13
      Caption = 'Sync width:'
    end
    object Back: TLabel
      Left = 25
      Top = 110
      Width = 56
      Height = 13
      Caption = 'Back porch:'
      OnClick = Last0Click
    end
    object Blank: TLabel
      Left = 25
      Top = 135
      Width = 43
      Height = 13
      Caption = 'Blanking:'
      OnClick = Last1Click
    end
    object Total: TLabel
      Left = 25
      Top = 160
      Width = 28
      Height = 13
      Caption = 'Total:'
      OnClick = Last2Click
    end
    object Polarity: TLabel
      Left = 25
      Top = 185
      Width = 66
      Height = 13
      Caption = 'Sync polarity:'
    end
    object Horizontal: TLabel
      Left = 101
      Top = 13
      Width = 58
      Height = 13
      Caption = 'Horizontal'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object ActivePixels: TLabel
      Left = 160
      Top = 35
      Width = 27
      Height = 13
      Caption = 'pixels'
    end
    object FrontPixels: TLabel
      Left = 160
      Top = 60
      Width = 27
      Height = 13
      Caption = 'pixels'
    end
    object SyncPixels: TLabel
      Left = 160
      Top = 85
      Width = 27
      Height = 13
      Caption = 'pixels'
    end
    object BackPixels: TLabel
      Left = 160
      Top = 110
      Width = 27
      Height = 13
      Caption = 'pixels'
    end
    object BlankPixels: TLabel
      Left = 160
      Top = 135
      Width = 27
      Height = 13
      Caption = 'pixels'
    end
    object TotalPixels: TLabel
      Left = 160
      Top = 160
      Width = 27
      Height = 13
      Caption = 'pixels'
    end
    object Vertical: TLabel
      Left = 213
      Top = 13
      Width = 43
      Height = 13
      Caption = 'Vertical'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object ActiveLines: TLabel
      Left = 265
      Top = 35
      Width = 21
      Height = 13
      Caption = 'lines'
    end
    object FrontLines: TLabel
      Left = 265
      Top = 60
      Width = 21
      Height = 13
      Caption = 'lines'
    end
    object SyncLines: TLabel
      Left = 265
      Top = 85
      Width = 21
      Height = 13
      Caption = 'lines'
    end
    object BackLines: TLabel
      Left = 265
      Top = 110
      Width = 21
      Height = 13
      Caption = 'lines'
    end
    object BlankLines: TLabel
      Left = 265
      Top = 135
      Width = 21
      Height = 13
      Caption = 'lines'
    end
    object TotalLines: TLabel
      Left = 265
      Top = 160
      Width = 21
      Height = 13
      Caption = 'lines'
    end
    object Last0: TRadioButton
      Left = 9
      Top = 108
      Width = 89
      Height = 17
      Caption = 'Back porch:'
      TabOrder = 0
      OnClick = Last0Click
    end
    object Last1: TRadioButton
      Left = 9
      Top = 133
      Width = 89
      Height = 17
      Caption = 'Blanking:'
      TabOrder = 1
      OnClick = Last1Click
    end
    object Last2: TRadioButton
      Left = 9
      Top = 158
      Width = 89
      Height = 17
      Caption = 'Total:'
      TabOrder = 2
      OnClick = Last2Click
    end
    object HActive: TEdit
      Left = 106
      Top = 32
      Width = 48
      Height = 21
      MaxLength = 5
      TabOrder = 3
      OnChange = HActiveChange
      OnExit = HActiveExit
    end
    object HFront: TEdit
      Left = 106
      Top = 57
      Width = 48
      Height = 21
      MaxLength = 5
      TabOrder = 4
      OnChange = HFrontChange
      OnExit = HFrontExit
    end
    object HSync: TEdit
      Left = 106
      Top = 82
      Width = 48
      Height = 21
      MaxLength = 5
      TabOrder = 5
      OnChange = HSyncChange
      OnExit = HSyncExit
    end
    object HBack: TEdit
      Left = 106
      Top = 107
      Width = 48
      Height = 21
      MaxLength = 5
      TabOrder = 6
      OnChange = HBackChange
      OnExit = HBackExit
    end
    object HBlank: TEdit
      Left = 106
      Top = 132
      Width = 48
      Height = 21
      MaxLength = 5
      TabOrder = 7
      OnChange = HBlankChange
      OnExit = HBlankExit
    end
    object HTotal: TEdit
      Left = 106
      Top = 157
      Width = 48
      Height = 21
      MaxLength = 6
      TabOrder = 8
      OnChange = HTotalChange
      OnExit = HTotalExit
    end
    object HPolarity: TComboBox
      Left = 106
      Top = 182
      Width = 48
      Height = 21
      Style = csDropDownList
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Courier'
      Font.Style = []
      ItemHeight = 13
      ParentFont = False
      TabOrder = 9
      OnChange = HPolarityChange
      Items.Strings = (
        ' -'
        ' +')
    end
    object VActive: TEdit
      Left = 211
      Top = 32
      Width = 48
      Height = 21
      MaxLength = 5
      TabOrder = 10
      OnChange = VActiveChange
      OnExit = VActiveExit
    end
    object VFront: TEdit
      Left = 211
      Top = 57
      Width = 48
      Height = 21
      MaxLength = 5
      TabOrder = 11
      OnChange = VFrontChange
      OnExit = VFrontExit
    end
    object VSync: TEdit
      Left = 211
      Top = 82
      Width = 48
      Height = 21
      MaxLength = 5
      TabOrder = 12
      OnChange = VSyncChange
      OnExit = VSyncExit
    end
    object VBack: TEdit
      Left = 211
      Top = 107
      Width = 48
      Height = 21
      MaxLength = 5
      TabOrder = 13
      OnChange = VBackChange
      OnExit = VBackExit
    end
    object VBlank: TEdit
      Left = 211
      Top = 132
      Width = 48
      Height = 21
      MaxLength = 5
      TabOrder = 14
      OnChange = VBlankChange
      OnExit = VBlankExit
    end
    object VTotal: TEdit
      Left = 211
      Top = 157
      Width = 48
      Height = 21
      MaxLength = 6
      TabOrder = 15
      OnChange = VTotalChange
      OnExit = VTotalExit
    end
    object VPolarity: TComboBox
      Left = 211
      Top = 182
      Width = 48
      Height = 21
      Style = csDropDownList
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Courier'
      Font.Style = []
      ItemHeight = 13
      ParentFont = False
      TabOrder = 16
      OnChange = VPolarityChange
      Items.Strings = (
        ' -'
        ' +')
    end
  end
  object FrequencyGroupBox: TGroupBox
    Left = 8
    Top = 253
    Width = 365
    Height = 100
    Caption = ' Frequency '
    ParentBackground = False
    TabOrder = 5
    object Rate0: TLabel
      Left = 25
      Top = 22
      Width = 65
      Height = 13
      Caption = 'Refresh rate:'
      OnClick = LastRate0Click
    end
    object Rate1: TLabel
      Left = 25
      Top = 47
      Width = 52
      Height = 13
      Caption = 'Horizontal:'
      OnClick = LastRate1Click
    end
    object Rate2: TLabel
      Left = 25
      Top = 72
      Width = 52
      Height = 13
      Caption = 'Pixel clock:'
      OnClick = LastRate2Click
    end
    object Hz: TLabel
      Left = 160
      Top = 22
      Width = 12
      Height = 13
      Caption = 'Hz'
    end
    object kHz: TLabel
      Left = 160
      Top = 47
      Width = 17
      Height = 13
      Caption = 'kHz'
    end
    object MHz: TLabel
      Left = 160
      Top = 72
      Width = 20
      Height = 13
      Caption = 'MHz'
    end
    object ActualVRate: TLabel
      Left = 211
      Top = 22
      Width = 58
      Height = 13
      Caption = 'Actual: '#8211' Hz'
    end
    object ActualHRate: TLabel
      Left = 211
      Top = 47
      Width = 63
      Height = 13
      Caption = 'Actual: '#8211' kHz'
    end
    object LastRate0: TRadioButton
      Left = 9
      Top = 20
      Width = 89
      Height = 17
      Caption = 'Refresh rate:'
      TabOrder = 0
      OnClick = LastRate0Click
    end
    object LastRate1: TRadioButton
      Left = 9
      Top = 45
      Width = 89
      Height = 17
      Caption = 'Horizontal:'
      TabOrder = 1
      OnClick = LastRate1Click
    end
    object LastRate2: TRadioButton
      Left = 9
      Top = 70
      Width = 89
      Height = 17
      Caption = 'Pixel clock:'
      TabOrder = 2
      OnClick = LastRate2Click
    end
    object VRate: TEdit
      Left = 106
      Top = 19
      Width = 48
      Height = 21
      MaxLength = 7
      TabOrder = 3
      OnChange = VRateChange
      OnExit = VRateExit
    end
    object HRate: TEdit
      Left = 106
      Top = 44
      Width = 48
      Height = 21
      MaxLength = 7
      TabOrder = 4
      OnChange = HRateChange
      OnExit = HRateExit
    end
    object PClock: TEdit
      Left = 106
      Top = 69
      Width = 48
      Height = 21
      MaxLength = 7
      TabOrder = 5
      OnChange = PClockChange
      OnExit = PClockExit
    end
    object Interlaced: TCheckBox
      Left = 211
      Top = 70
      Width = 67
      Height = 17
      Caption = 'Interlaced'
      TabOrder = 6
      OnClick = InterlacedClick
    end
    object Native: TCheckBox
      Left = 292
      Top = 70
      Width = 49
      Height = 17
      Caption = 'Native'
      TabOrder = 7
      OnClick = NativeClick
    end
  end
  object FormOKButton: TButton
    Left = 218
    Top = 359
    Width = 75
    Height = 23
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 6
  end
  object FormCancelButton: TButton
    Left = 299
    Top = 359
    Width = 75
    Height = 23
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 7
  end
end
