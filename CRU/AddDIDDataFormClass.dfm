object AddDIDDataForm: TAddDIDDataForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Add Data Block'
  ClientHeight = 101
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
  object TypeGroupBox: TGroupBox
    Left = 8
    Top = 6
    Width = 154
    Height = 59
    Caption = ' Type '
    TabOrder = 0
    object DetailedResolutionsRadioButton: TRadioButton
      Left = 9
      Top = 17
      Width = 112
      Height = 17
      Caption = 'Detailed resolutions'
      TabOrder = 0
      OnClick = DetailedResolutionsRadioButtonClick
    end
    object TiledDisplayTopologyRadioButton: TRadioButton
      Left = 9
      Top = 34
      Width = 121
      Height = 17
      Caption = 'Tiled display topology'
      TabOrder = 1
      OnClick = TiledDisplayTopologyRadioButtonClick
    end
  end
  object FormOKButton: TButton
    Left = 7
    Top = 71
    Width = 75
    Height = 23
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 1
  end
  object FormCancelButton: TButton
    Left = 88
    Top = 71
    Width = 75
    Height = 23
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 2
  end
end
