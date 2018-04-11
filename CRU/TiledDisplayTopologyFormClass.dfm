object TiledDisplayTopologyForm: TTiledDisplayTopologyForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Tiled Display Topology'
  ClientHeight = 663
  ClientWidth = 170
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
  object PhysicalEnclosuresGroupBox: TGroupBox
    Left = 8
    Top = 6
    Width = 154
    Height = 59
    Caption = ' Physical display enclosures '
    TabOrder = 0
    object PhysicalEnclosuresRadioButton1: TRadioButton
      Tag = 1
      Left = 9
      Top = 17
      Width = 46
      Height = 17
      Caption = 'Single'
      TabOrder = 0
      OnClick = EnclosuresRadioButtonClick
    end
    object PhysicalEnclosuresRadioButton0: TRadioButton
      Left = 9
      Top = 34
      Width = 54
      Height = 17
      Caption = 'Multiple'
      TabOrder = 1
      OnClick = EnclosuresRadioButtonClick
    end
  end
  object SingleTileBehaviorGroupBox: TGroupBox
    Left = 8
    Top = 70
    Width = 154
    Height = 93
    Caption = ' Single-tile behavior '
    TabOrder = 1
    object SingleTileBehaviorRadioButton1: TRadioButton
      Tag = 1
      Left = 9
      Top = 17
      Width = 117
      Height = 17
      Caption = 'Displayed at location'
      TabOrder = 0
      OnClick = SingleTileBehaviorRadioButtonClick
    end
    object SingleTileBehaviorRadioButton2: TRadioButton
      Tag = 2
      Left = 9
      Top = 34
      Width = 111
      Height = 17
      Caption = 'Scaled to fit display'
      TabOrder = 1
      OnClick = SingleTileBehaviorRadioButtonClick
    end
    object SingleTileBehaviorRadioButton3: TRadioButton
      Tag = 3
      Left = 9
      Top = 51
      Width = 115
      Height = 17
      Caption = 'Cloned to other tiles'
      TabOrder = 2
      OnClick = SingleTileBehaviorRadioButtonClick
    end
    object SingleTileBehaviorRadioButton0: TRadioButton
      Left = 9
      Top = 68
      Width = 46
      Height = 17
      Caption = 'Other'
      TabOrder = 3
      OnClick = SingleTileBehaviorRadioButtonClick
    end
  end
  object MultipleTileBehaviorGroupBox: TGroupBox
    Left = 8
    Top = 168
    Width = 154
    Height = 59
    Caption = ' Multiple-tile behavior '
    TabOrder = 2
    object MultipleTileBehaviorRadioButton1: TRadioButton
      Tag = 1
      Left = 9
      Top = 17
      Width = 117
      Height = 17
      Caption = 'Displayed at location'
      TabOrder = 0
      OnClick = MultipleTileBehaviorRadioButtonClick
    end
    object MultipleTileBehaviorRadioButton0: TRadioButton
      Left = 9
      Top = 34
      Width = 46
      Height = 17
      Caption = 'Other'
      TabOrder = 1
      OnClick = MultipleTileBehaviorRadioButtonClick
    end
  end
  object TilesGroupBox: TGroupBox
    Left = 8
    Top = 232
    Width = 154
    Height = 50
    Caption = ' Number of tiles '
    TabOrder = 3
    object TilesLabel: TLabel
      Left = 37
      Top = 22
      Width = 6
      Height = 13
      Caption = 'x'
    end
    object HTiles: TEdit
      Left = 9
      Top = 19
      Width = 24
      Height = 21
      MaxLength = 2
      TabOrder = 0
      OnChange = HTilesChange
      OnExit = HTilesExit
    end
    object VTiles: TEdit
      Left = 47
      Top = 19
      Width = 24
      Height = 21
      MaxLength = 2
      TabOrder = 1
      OnChange = VTilesChange
      OnExit = VTilesExit
    end
  end
  object LocationGroupBox: TGroupBox
    Left = 8
    Top = 287
    Width = 154
    Height = 50
    Caption = ' Tile location '
    TabOrder = 4
    object LocationLabel: TLabel
      Left = 37
      Top = 22
      Width = 4
      Height = 13
      Caption = ','
    end
    object HLocation: TEdit
      Left = 9
      Top = 19
      Width = 24
      Height = 21
      MaxLength = 2
      TabOrder = 0
      OnChange = HLocationChange
      OnExit = HLocationExit
    end
    object VLocation: TEdit
      Left = 47
      Top = 19
      Width = 24
      Height = 21
      MaxLength = 2
      TabOrder = 1
      OnChange = VLocationChange
      OnExit = VLocationExit
    end
  end
  object SizeGroupBox: TGroupBox
    Left = 8
    Top = 342
    Width = 154
    Height = 50
    Caption = ' Tile size '
    TabOrder = 5
    object SizeLabel: TLabel
      Left = 49
      Top = 22
      Width = 6
      Height = 13
      Caption = 'x'
    end
    object HSize: TEdit
      Left = 9
      Top = 19
      Width = 36
      Height = 21
      MaxLength = 5
      TabOrder = 0
      OnChange = HSizeChange
      OnExit = HSizeExit
    end
    object VSize: TEdit
      Left = 59
      Top = 19
      Width = 36
      Height = 21
      MaxLength = 5
      TabOrder = 1
      OnChange = VSizeChange
      OnExit = VSizeExit
    end
  end
  object BezelGroupBox: TGroupBox
    Left = 8
    Top = 397
    Width = 154
    Height = 150
    Caption = ' Bezel size '
    TabOrder = 6
    object MultiplierLabel: TLabel
      Left = 9
      Top = 22
      Width = 46
      Height = 13
      Caption = 'Multiplier:'
    end
    object TopLabel: TLabel
      Left = 9
      Top = 47
      Width = 22
      Height = 13
      Caption = 'Top:'
    end
    object BottomLabel: TLabel
      Left = 9
      Top = 72
      Width = 38
      Height = 13
      Caption = 'Bottom:'
    end
    object RightLabel: TLabel
      Left = 9
      Top = 97
      Width = 29
      Height = 13
      Caption = 'Right:'
    end
    object LeftLabel: TLabel
      Left = 9
      Top = 122
      Width = 23
      Height = 13
      Caption = 'Left:'
    end
    object PixelMultiplier: TEdit
      Left = 59
      Top = 19
      Width = 24
      Height = 21
      MaxLength = 3
      TabOrder = 0
      OnChange = PixelMultiplierChange
      OnExit = PixelMultiplierExit
    end
    object TopBezelSize: TEdit
      Left = 59
      Top = 44
      Width = 24
      Height = 21
      MaxLength = 3
      TabOrder = 1
      OnChange = TopBezelSizeChange
      OnExit = TopBezelSizeExit
    end
    object BottomBezelSize: TEdit
      Left = 59
      Top = 69
      Width = 24
      Height = 21
      MaxLength = 3
      TabOrder = 2
      OnChange = BottomBezelSizeChange
      OnExit = BottomBezelSizeExit
    end
    object RightBezelSize: TEdit
      Left = 59
      Top = 94
      Width = 24
      Height = 21
      MaxLength = 3
      TabOrder = 3
      OnChange = RightBezelSizeChange
      OnExit = RightBezelSizeExit
    end
    object LeftBezelSize: TEdit
      Left = 59
      Top = 119
      Width = 24
      Height = 21
      MaxLength = 3
      TabOrder = 4
      OnChange = LeftBezelSizeChange
      OnExit = LeftBezelSizeExit
    end
  end
  object TopologyIDGroupBox: TGroupBox
    Left = 8
    Top = 552
    Width = 154
    Height = 75
    Caption = ' Topology ID '
    TabOrder = 7
    object ProductIDLabel: TLabel
      Left = 9
      Top = 22
      Width = 15
      Height = 13
      Caption = 'ID:'
    end
    object SerialIDLabel: TLabel
      Left = 9
      Top = 47
      Width = 54
      Height = 13
      Caption = 'ID serial #:'
    end
    object ProductID: TEdit
      Left = 28
      Top = 19
      Width = 69
      Height = 21
      MaxLength = 7
      TabOrder = 0
      OnChange = ProductIDChange
      OnExit = ProductIDExit
      OnKeyPress = ProductIDKeyPress
    end
    object SerialID: TEdit
      Left = 67
      Top = 44
      Width = 79
      Height = 21
      MaxLength = 10
      TabOrder = 1
      OnChange = SerialIDChange
      OnExit = SerialIDExit
    end
    object ProductIDResetButton: TButton
      Left = 104
      Top = 19
      Width = 42
      Height = 21
      Caption = 'Reset'
      TabOrder = 2
      OnClick = ProductIDResetButtonClick
    end
  end
  object FormOKButton: TButton
    Left = 7
    Top = 633
    Width = 75
    Height = 23
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 8
  end
  object FormCancelButton: TButton
    Left = 88
    Top = 633
    Width = 75
    Height = 23
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 9
  end
end
