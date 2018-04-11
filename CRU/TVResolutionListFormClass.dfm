object TVResolutionListForm: TTVResolutionListForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'TV Resolutions'
  ClientHeight = 310
  ClientWidth = 376
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
  object TVGroupBox: TGroupBox
    Left = 8
    Top = 6
    Width = 360
    Height = 268
    Caption = ' TV resolutions '
    TabOrder = 1
    object TVListBox: TListBox
      Left = 9
      Top = 19
      Width = 342
      Height = 212
      Style = lbOwnerDrawFixed
      Columns = 2
      ItemHeight = 13
      TabOrder = 0
      OnClick = TVListBoxSelect
      OnDblClick = TVListBoxDoubleClick
      OnDrawItem = TVListBoxDrawItem
      OnMouseDown = TVListBoxClick
    end
    object TVAddButton: TButton
      Left = 8
      Top = 238
      Width = 42
      Height = 21
      Caption = 'Add...'
      TabOrder = 1
      OnClick = TVAddButtonClick
    end
    object TVEditButton: TButton
      Left = 50
      Top = 238
      Width = 42
      Height = 21
      Caption = 'Edit...'
      TabOrder = 2
      OnClick = TVEditButtonClick
    end
    object TVDeleteButton: TButton
      Left = 92
      Top = 238
      Width = 42
      Height = 21
      Caption = 'Delete'
      TabOrder = 3
      OnClick = TVDeleteButtonClick
    end
    object TVDeleteAllButton: TButton
      Left = 134
      Top = 238
      Width = 56
      Height = 21
      Caption = 'Delete all'
      TabOrder = 4
      OnClick = TVDeleteAllButtonClick
    end
    object TVResetButton: TButton
      Left = 190
      Top = 238
      Width = 42
      Height = 21
      Caption = 'Reset'
      TabOrder = 5
      OnClick = TVResetButtonClick
    end
    object TVUpButton: TBitBtn
      Left = 310
      Top = 238
      Width = 21
      Height = 21
      TabOrder = 6
      OnClick = TVUpButtonClick
      Glyph.Data = {
        6A000000424D6A000000000000003E00000028000000090000000B0000000100
        0100000000002C0000000000000000000000020000000000000000000000FFFF
        FF00FF800000E3800000E3800000E3800000E3800000E380000080800000C180
        0000E3800000F7800000FF800000}
    end
    object TVDownButton: TBitBtn
      Left = 331
      Top = 238
      Width = 21
      Height = 21
      TabOrder = 7
      OnClick = TVDownButtonClick
      Glyph.Data = {
        6A000000424D6A000000000000003E00000028000000090000000B0000000100
        0100000000002C0000000000000000000000020000000000000000000000FFFF
        FF00FF800000F7800000E3800000C180000080800000E3800000E3800000E380
        0000E3800000E3800000FF800000}
    end
  end
  object YCbCr420: TCheckBox
    Left = 261
    Top = 4
    Width = 99
    Height = 17
    Caption = '4:2:0 resolutions'
    TabOrder = 0
    OnClick = YCbCr420Click
  end
  object FormOKButton: TButton
    Left = 213
    Top = 280
    Width = 75
    Height = 23
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 2
  end
  object FormCancelButton: TButton
    Left = 294
    Top = 280
    Width = 75
    Height = 23
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 3
  end
end
