object AudioFormatListForm: TAudioFormatListForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Audio Formats'
  ClientHeight = 232
  ClientWidth = 346
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
  object AudioGroupBox: TGroupBox
    Left = 8
    Top = 6
    Width = 330
    Height = 190
    Caption = ' Audio formats '
    TabOrder = 0
    object AudioListBox: TListBox
      Left = 9
      Top = 19
      Width = 312
      Height = 134
      Style = lbOwnerDrawFixed
      ItemHeight = 13
      TabOrder = 0
      OnClick = AudioListBoxSelect
      OnDblClick = AudioListBoxDoubleClick
      OnDrawItem = AudioListBoxDrawItem
      OnMouseDown = AudioListBoxClick
    end
    object AudioAddButton: TButton
      Left = 8
      Top = 160
      Width = 42
      Height = 21
      Caption = 'Add...'
      TabOrder = 1
      OnClick = AudioAddButtonClick
    end
    object AudioEditButton: TButton
      Left = 50
      Top = 160
      Width = 42
      Height = 21
      Caption = 'Edit...'
      TabOrder = 2
      OnClick = AudioEditButtonClick
    end
    object AudioDeleteButton: TButton
      Left = 92
      Top = 160
      Width = 42
      Height = 21
      Caption = 'Delete'
      TabOrder = 3
      OnClick = AudioDeleteButtonClick
    end
    object AudioDeleteAllButton: TButton
      Left = 134
      Top = 160
      Width = 56
      Height = 21
      Caption = 'Delete all'
      TabOrder = 4
      OnClick = AudioDeleteAllButtonClick
    end
    object AudioResetButton: TButton
      Left = 190
      Top = 160
      Width = 42
      Height = 21
      Caption = 'Reset'
      TabOrder = 5
      OnClick = AudioResetButtonClick
    end
    object AudioUpButton: TBitBtn
      Left = 280
      Top = 160
      Width = 21
      Height = 21
      TabOrder = 6
      OnClick = AudioUpButtonClick
      Glyph.Data = {
        6A000000424D6A000000000000003E00000028000000090000000B0000000100
        0100000000002C0000000000000000000000020000000000000000000000FFFF
        FF00FF800000E3800000E3800000E3800000E3800000E380000080800000C180
        0000E3800000F7800000FF800000}
    end
    object AudioDownButton: TBitBtn
      Left = 301
      Top = 160
      Width = 21
      Height = 21
      TabOrder = 7
      OnClick = AudioDownButtonClick
      Glyph.Data = {
        6A000000424D6A000000000000003E00000028000000090000000B0000000100
        0100000000002C0000000000000000000000020000000000000000000000FFFF
        FF00FF800000F7800000E3800000C180000080800000E3800000E3800000E380
        0000E3800000E3800000FF800000}
    end
  end
  object FormOKButton: TButton
    Left = 183
    Top = 202
    Width = 75
    Height = 23
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 1
  end
  object FormCancelButton: TButton
    Left = 264
    Top = 202
    Width = 75
    Height = 23
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 2
  end
end
