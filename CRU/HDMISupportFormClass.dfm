object HDMISupportForm: THDMISupportForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'HDMI Support'
  ClientHeight = 557
  ClientWidth = 332
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
  object PhysicalAddressGroupBox: TGroupBox
    Left = 8
    Top = 6
    Width = 316
    Height = 50
    Caption = ' Source physical address '
    TabOrder = 0
    object PhysicalAddressLabel: TLabel
      Left = 131
      Top = 22
      Width = 47
      Height = 13
      Caption = '(A.B.C.D)'
    end
    object PhysicalAddress: TEdit
      Left = 9
      Top = 19
      Width = 116
      Height = 21
      MaxLength = 11
      TabOrder = 0
      OnChange = PhysicalAddressChange
      OnExit = PhysicalAddressExit
    end
  end
  object ColorFormatsGroupBox: TGroupBox
    Left = 8
    Top = 61
    Width = 316
    Height = 76
    Caption = ' Color formats '
    TabOrder = 1
    object YCbCr422: TCheckBox
      Left = 9
      Top = 17
      Width = 77
      Height = 17
      Caption = 'YCbCr 4:2:2'
      TabOrder = 0
      OnClick = YCbCr422Click
    end
    object YCbCr444: TCheckBox
      Left = 9
      Top = 34
      Width = 77
      Height = 17
      Caption = 'YCbCr 4:4:4'
      TabOrder = 1
      OnClick = YCbCr444Click
    end
    object DeepColorYCbCr444: TCheckBox
      Left = 9
      Top = 51
      Width = 130
      Height = 17
      Caption = 'YCbCr 4:4:4 deep color'
      TabOrder = 2
      OnClick = DeepColorYCbCr444Click
    end
    object DeepColor30bit: TCheckBox
      Left = 162
      Top = 17
      Width = 142
      Height = 17
      Caption = '30-bit deep color (10 bpc)'
      TabOrder = 3
      OnClick = DeepColor30bitClick
    end
    object DeepColor36bit: TCheckBox
      Left = 162
      Top = 34
      Width = 142
      Height = 17
      Caption = '36-bit deep color (12 bpc)'
      TabOrder = 4
      OnClick = DeepColor36bitClick
    end
    object DeepColor48bit: TCheckBox
      Left = 162
      Top = 51
      Width = 142
      Height = 17
      Caption = '48-bit deep color (16 bpc)'
      TabOrder = 5
      OnClick = DeepColor48bitClick
    end
  end
  object FeaturesGroupBox: TGroupBox
    Left = 8
    Top = 142
    Width = 316
    Height = 59
    Caption = ' Supported features '
    TabOrder = 2
    object SupportsAI: TCheckBox
      Left = 9
      Top = 17
      Width = 147
      Height = 17
      Caption = 'Supports audio information'
      TabOrder = 0
      OnClick = SupportsAIClick
    end
    object DualLinkDVI: TCheckBox
      Left = 9
      Top = 34
      Width = 172
      Height = 17
      Caption = 'Supports DVI dual-link operation'
      TabOrder = 1
      OnClick = DualLinkDVIClick
    end
  end
  object TMDSClockGroupBox: TGroupBox
    Left = 8
    Top = 206
    Width = 316
    Height = 50
    Caption = ' Maximum TMDS clock '
    TabOrder = 3
    object TMDSClockLabel: TLabel
      Left = 214
      Top = 22
      Width = 20
      Height = 13
      Caption = 'MHz'
    end
    object OverrideTMDSClock: TCheckBox
      Left = 9
      Top = 20
      Width = 167
      Height = 17
      Caption = 'Override maximum TMDS clock:'
      TabOrder = 0
      OnClick = OverrideTMDSClockClick
    end
    object TMDSClock: TEdit
      Left = 178
      Top = 19
      Width = 30
      Height = 21
      MaxLength = 4
      TabOrder = 1
      OnChange = TMDSClockChange
      OnExit = TMDSClockExit
    end
  end
  object ContentTypesGroupBox: TGroupBox
    Left = 8
    Top = 261
    Width = 316
    Height = 42
    Caption = ' Supported content types '
    TabOrder = 4
    object ContentType0: TCheckBox
      Left = 9
      Top = 17
      Width = 59
      Height = 17
      Caption = 'Graphics'
      TabOrder = 0
      OnClick = ContentTypeClick
    end
    object ContentType1: TCheckBox
      Tag = 1
      Left = 92
      Top = 17
      Width = 46
      Height = 17
      Caption = 'Photo'
      TabOrder = 1
      OnClick = ContentTypeClick
    end
    object ContentType2: TCheckBox
      Tag = 2
      Left = 162
      Top = 17
      Width = 53
      Height = 17
      Caption = 'Cinema'
      TabOrder = 2
      OnClick = ContentTypeClick
    end
    object ContentType3: TCheckBox
      Tag = 3
      Left = 239
      Top = 17
      Width = 45
      Height = 17
      Caption = 'Game'
      TabOrder = 3
      OnClick = ContentTypeClick
    end
  end
  object LatencyGroupBox: TGroupBox
    Left = 8
    Top = 308
    Width = 316
    Height = 96
    Caption = ' Latency information '
    TabOrder = 5
    object VideoLatencyLabel: TLabel
      Left = 110
      Top = 43
      Width = 13
      Height = 13
      Caption = 'ms'
    end
    object AudioLatencyLabel: TLabel
      Left = 110
      Top = 68
      Width = 13
      Height = 13
      Caption = 'ms'
    end
    object InterlacedVideoLatencyLabel: TLabel
      Left = 263
      Top = 43
      Width = 13
      Height = 13
      Caption = 'ms'
    end
    object InterlacedAudioLatencyLabel: TLabel
      Left = 263
      Top = 68
      Width = 13
      Height = 13
      Caption = 'ms'
    end
    object IncludeLatency: TCheckBox
      Left = 9
      Top = 17
      Width = 120
      Height = 17
      Caption = 'Include latency data:'
      TabOrder = 0
      OnClick = IncludeLatencyClick
    end
    object VideoSupported: TCheckBox
      Left = 29
      Top = 41
      Width = 48
      Height = 17
      Caption = 'Video:'
      TabOrder = 1
      OnClick = VideoSupportedClick
    end
    object VideoLatency: TEdit
      Left = 80
      Top = 40
      Width = 24
      Height = 21
      MaxLength = 3
      TabOrder = 2
      OnChange = VideoLatencyChange
      OnExit = VideoLatencyExit
    end
    object AudioSupported: TCheckBox
      Left = 29
      Top = 66
      Width = 49
      Height = 17
      Caption = 'Audio:'
      TabOrder = 3
      OnClick = AudioSupportedClick
    end
    object AudioLatency: TEdit
      Left = 80
      Top = 65
      Width = 24
      Height = 21
      MaxLength = 3
      TabOrder = 4
      OnChange = AudioLatencyChange
      OnExit = AudioLatencyExit
    end
    object IncludeInterlacedLatency: TCheckBox
      Left = 162
      Top = 17
      Width = 132
      Height = 17
      Caption = 'Include interlaced data:'
      TabOrder = 5
      OnClick = IncludeInterlacedLatencyClick
    end
    object InterlacedVideoSupported: TCheckBox
      Left = 182
      Top = 41
      Width = 48
      Height = 17
      Caption = 'Video:'
      TabOrder = 6
      OnClick = InterlacedVideoSupportedClick
    end
    object InterlacedVideoLatency: TEdit
      Left = 233
      Top = 40
      Width = 24
      Height = 21
      MaxLength = 3
      TabOrder = 7
      OnChange = InterlacedVideoLatencyChange
      OnExit = InterlacedVideoLatencyExit
    end
    object InterlacedAudioSupported: TCheckBox
      Left = 182
      Top = 66
      Width = 49
      Height = 17
      Caption = 'Audio:'
      TabOrder = 8
      OnClick = InterlacedAudioSupportedClick
    end
    object InterlacedAudioLatency: TEdit
      Left = 233
      Top = 65
      Width = 24
      Height = 21
      MaxLength = 3
      TabOrder = 9
      OnChange = InterlacedAudioLatencyChange
      OnExit = InterlacedAudioLatencyExit
    end
  end
  object HDMIResolutionsGroupBox: TGroupBox
    Left = 8
    Top = 409
    Width = 316
    Height = 112
    Caption = ' HDMI resolutions '
    ParentBackground = False
    TabOrder = 6
    object HDMIResolutionsListBox: TListBox
      Left = 9
      Top = 19
      Width = 298
      Height = 56
      Style = lbOwnerDrawFixed
      Columns = 2
      ItemHeight = 13
      TabOrder = 0
      OnClick = HDMIResolutionsListBoxSelect
      OnDblClick = HDMIResolutionsListBoxDblClick
      OnDrawItem = HDMIResolutionsListBoxDrawItem
      OnMouseDown = HDMIResolutionsListBoxClick
    end
    object HDMIResolutionsAddButton: TButton
      Left = 8
      Top = 82
      Width = 42
      Height = 21
      Caption = 'Add...'
      TabOrder = 1
      OnClick = HDMIResolutionsAddButtonClick
    end
    object HDMIResolutionsEditButton: TButton
      Left = 50
      Top = 82
      Width = 42
      Height = 21
      Caption = 'Edit...'
      TabOrder = 2
      OnClick = HDMIResolutionsEditButtonClick
    end
    object HDMIResolutionsDeleteButton: TButton
      Left = 92
      Top = 82
      Width = 42
      Height = 21
      Caption = 'Delete'
      TabOrder = 3
      OnClick = HDMIResolutionsDeleteButtonClick
    end
    object HDMIResolutionsDeleteAllButton: TButton
      Left = 134
      Top = 82
      Width = 56
      Height = 21
      Caption = 'Delete all'
      TabOrder = 4
      OnClick = HDMIResolutionsDeleteAllButtonClick
    end
    object HDMIResolutionsResetButton: TButton
      Left = 190
      Top = 82
      Width = 42
      Height = 21
      Caption = 'Reset'
      TabOrder = 5
      OnClick = HDMIResolutionsResetButtonClick
    end
    object HDMIResolutionsUpButton: TBitBtn
      Left = 266
      Top = 82
      Width = 21
      Height = 21
      TabOrder = 6
      OnClick = HDMIResolutionsUpButtonClick
      Glyph.Data = {
        6A000000424D6A000000000000003E00000028000000090000000B0000000100
        0100000000002C0000000000000000000000020000000000000000000000FFFF
        FF00FF800000E3800000E3800000E3800000E3800000E380000080800000C180
        0000E3800000F7800000FF800000}
    end
    object HDMIResolutionsDownButton: TBitBtn
      Left = 287
      Top = 82
      Width = 21
      Height = 21
      TabOrder = 7
      OnClick = HDMIResolutionsDownButtonClick
      Glyph.Data = {
        6A000000424D6A000000000000003E00000028000000090000000B0000000100
        0100000000002C0000000000000000000000020000000000000000000000FFFF
        FF00FF800000F7800000E3800000C180000080800000E3800000E3800000E380
        0000E3800000E3800000FF800000}
    end
  end
  object FormOKButton: TButton
    Left = 169
    Top = 527
    Width = 75
    Height = 23
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 7
  end
  object FormCancelButton: TButton
    Left = 250
    Top = 527
    Width = 75
    Height = 23
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 8
  end
end
