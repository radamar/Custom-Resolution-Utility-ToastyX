object DIDDetailedResolutionListForm: TDIDDetailedResolutionListForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Detailed Resolutions'
  ClientHeight = 167
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
  object DetailedGroupBox: TGroupBox
    Left = 8
    Top = 6
    Width = 330
    Height = 125
    Caption = ' Detailed resolutions '
    TabOrder = 0
    object DetailedListBox: TListBox
      Left = 9
      Top = 19
      Width = 312
      Height = 69
      Style = lbOwnerDrawFixed
      ItemHeight = 13
      TabOrder = 0
      OnClick = DetailedListBoxSelect
      OnDblClick = DetailedListBoxDoubleClick
      OnDrawItem = DetailedListBoxDrawItem
      OnMouseDown = DetailedListBoxClick
    end
    object DetailedAddButton: TButton
      Left = 8
      Top = 95
      Width = 42
      Height = 21
      Caption = 'Add...'
      TabOrder = 1
      OnClick = DetailedAddButtonClick
    end
    object DetailedEditButton: TButton
      Left = 50
      Top = 95
      Width = 42
      Height = 21
      Caption = 'Edit...'
      TabOrder = 2
      OnClick = DetailedEditButtonClick
    end
    object DetailedDeleteButton: TButton
      Left = 92
      Top = 95
      Width = 42
      Height = 21
      Caption = 'Delete'
      TabOrder = 3
      OnClick = DetailedDeleteButtonClick
    end
    object DetailedDeleteAllButton: TButton
      Left = 134
      Top = 95
      Width = 56
      Height = 21
      Caption = 'Delete all'
      TabOrder = 4
      OnClick = DetailedDeleteAllButtonClick
    end
    object DetailedResetButton: TButton
      Left = 190
      Top = 95
      Width = 42
      Height = 21
      Caption = 'Reset'
      TabOrder = 5
      OnClick = DetailedResetButtonClick
    end
    object DetailedUpButton: TBitBtn
      Left = 280
      Top = 95
      Width = 21
      Height = 21
      TabOrder = 6
      OnClick = DetailedUpButtonClick
      Glyph.Data = {
        6A000000424D6A000000000000003E00000028000000090000000B0000000100
        0100000000002C0000000000000000000000020000000000000000000000FFFF
        FF00FF800000E3800000E3800000E3800000E3800000E380000080800000C180
        0000E3800000F7800000FF800000}
    end
    object DetailedDownButton: TBitBtn
      Left = 301
      Top = 95
      Width = 21
      Height = 21
      TabOrder = 7
      OnClick = DetailedDownButtonClick
      Glyph.Data = {
        6A000000424D6A000000000000003E00000028000000090000000B0000000100
        0100000000002C0000000000000000000000020000000000000000000000FFFF
        FF00FF800000F7800000E3800000C180000080800000E3800000E3800000E380
        0000E3800000E3800000FF800000}
    end
  end
  object FormOKButton: TButton
    Left = 183
    Top = 137
    Width = 75
    Height = 23
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 1
  end
  object FormCancelButton: TButton
    Left = 264
    Top = 137
    Width = 75
    Height = 23
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 2
  end
end
