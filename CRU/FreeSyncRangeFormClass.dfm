object FreeSyncRangeForm: TFreeSyncRangeForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'FreeSync Range'
  ClientHeight = 92
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
  object RangeLimitsGroupBox: TGroupBox
    Left = 8
    Top = 6
    Width = 154
    Height = 50
    Caption = ' Range limits '
    TabOrder = 0
    object VRateLabel: TLabel
      Left = 9
      Top = 22
      Width = 33
      Height = 13
      Caption = 'V rate:'
    end
    object VRateDash: TShape
      Left = 77
      Top = 29
      Width = 6
      Height = 1
      Brush.Color = clWindowText
      Pen.Color = clWindowText
    end
    object HzLabel: TLabel
      Left = 118
      Top = 22
      Width = 12
      Height = 13
      Caption = 'Hz'
    end
    object MinVRate: TEdit
      Left = 48
      Top = 19
      Width = 24
      Height = 21
      MaxLength = 3
      TabOrder = 0
      OnChange = MinVRateChange
      OnExit = MinVRateExit
    end
    object MaxVRate: TEdit
      Left = 88
      Top = 19
      Width = 24
      Height = 21
      MaxLength = 3
      TabOrder = 1
      OnChange = MaxVRateChange
      OnExit = MaxVRateExit
    end
  end
  object FormOKButton: TButton
    Left = 7
    Top = 62
    Width = 75
    Height = 23
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 1
  end
  object FormCancelButton: TButton
    Left = 88
    Top = 62
    Width = 75
    Height = 23
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 2
  end
end
