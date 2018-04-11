object ExtensionBlockForm: TExtensionBlockForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Extension Block'
  ClientHeight = 859
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
  object ExtensionTypeLabel: TLabel
    Left = 8
    Top = 12
    Width = 28
    Height = 13
    Caption = 'Type:'
  end
  object DefaultOutline: TShape
    Left = 8
    Top = 829
    Width = 169
    Height = 23
    Brush.Style = bsClear
    Pen.Color = clGrayText
    Pen.Style = psDot
  end
  object DefaultLabel: TLabel
    Left = 17
    Top = 834
    Width = 112
    Height = 13
    Caption = 'Default extension block'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clGrayText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object ExtensionTypeComboBox: TComboBox
    Left = 40
    Top = 8
    Width = 166
    Height = 21
    Style = csDropDownList
    ItemHeight = 0
    TabOrder = 0
    OnChange = ExtensionTypeComboBoxChange
  end
  object ExtensionCopyButton: TButton
    Left = 213
    Top = 8
    Width = 42
    Height = 21
    Caption = 'Copy'
    TabOrder = 1
    OnClick = ExtensionCopyButtonClick
  end
  object ExtensionPasteButton: TButton
    Left = 255
    Top = 8
    Width = 42
    Height = 21
    Caption = 'Paste'
    TabOrder = 2
    OnClick = ExtensionPasteButtonClick
  end
  object ExtensionResetButton: TButton
    Left = 297
    Top = 8
    Width = 42
    Height = 21
    Caption = 'Reset'
    TabOrder = 3
    OnClick = ExtensionResetButtonClick
  end
  object DetailedGroupBox: TGroupBox
    Left = 8
    Top = 35
    Width = 330
    Height = 138
    Caption = ' Detailed resolutions '
    ParentBackground = False
    TabOrder = 4
    object DetailedListBox: TListBox
      Left = 9
      Top = 19
      Width = 312
      Height = 82
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
      Top = 108
      Width = 42
      Height = 21
      Caption = 'Add...'
      TabOrder = 1
      OnClick = DetailedAddButtonClick
    end
    object DetailedEditButton: TButton
      Left = 50
      Top = 108
      Width = 42
      Height = 21
      Caption = 'Edit...'
      TabOrder = 2
      OnClick = DetailedEditButtonClick
    end
    object DetailedDeleteButton: TButton
      Left = 92
      Top = 108
      Width = 42
      Height = 21
      Caption = 'Delete'
      TabOrder = 3
      OnClick = DetailedDeleteButtonClick
    end
    object DetailedDeleteAllButton: TButton
      Left = 134
      Top = 108
      Width = 56
      Height = 21
      Caption = 'Delete all'
      TabOrder = 4
      OnClick = DetailedDeleteAllButtonClick
    end
    object DetailedResetButton: TButton
      Left = 190
      Top = 108
      Width = 42
      Height = 21
      Caption = 'Reset'
      TabOrder = 5
      OnClick = DetailedResetButtonClick
    end
    object DetailedUpButton: TBitBtn
      Left = 280
      Top = 108
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
      Top = 108
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
  object CEADataGroupBox: TGroupBox
    Left = 8
    Top = 178
    Width = 330
    Height = 164
    Caption = ' Data blocks '
    ParentBackground = False
    TabOrder = 5
    object CEADataListBox: TListBox
      Left = 9
      Top = 19
      Width = 312
      Height = 108
      Style = lbOwnerDrawFixed
      ItemHeight = 13
      TabOrder = 0
      OnClick = CEADataListBoxSelect
      OnDblClick = CEADataListBoxDoubleClick
      OnDrawItem = CEADataListBoxDrawItem
      OnMouseDown = CEADataListBoxClick
    end
    object CEADataAddButton: TButton
      Left = 8
      Top = 134
      Width = 42
      Height = 21
      Caption = 'Add...'
      TabOrder = 1
      OnClick = CEADataAddButtonClick
    end
    object CEADataEditButton: TButton
      Left = 50
      Top = 134
      Width = 42
      Height = 21
      Caption = 'Edit...'
      TabOrder = 2
      OnClick = CEADataEditButtonClick
    end
    object CEADataDeleteButton: TButton
      Left = 92
      Top = 134
      Width = 42
      Height = 21
      Caption = 'Delete'
      TabOrder = 3
      OnClick = CEADataDeleteButtonClick
    end
    object CEADataDeleteAllButton: TButton
      Left = 134
      Top = 134
      Width = 56
      Height = 21
      Caption = 'Delete all'
      TabOrder = 4
      OnClick = CEADataDeleteAllButtonClick
    end
    object CEADataResetButton: TButton
      Left = 190
      Top = 134
      Width = 42
      Height = 21
      Caption = 'Reset'
      TabOrder = 5
      OnClick = CEADataResetButtonClick
    end
    object CEADataUpButton: TBitBtn
      Left = 280
      Top = 134
      Width = 21
      Height = 21
      TabOrder = 6
      OnClick = CEADataUpButtonClick
      Glyph.Data = {
        6A000000424D6A000000000000003E00000028000000090000000B0000000100
        0100000000002C0000000000000000000000020000000000000000000000FFFF
        FF00FF800000E3800000E3800000E3800000E3800000E380000080800000C180
        0000E3800000F7800000FF800000}
    end
    object CEADataDownButton: TBitBtn
      Left = 301
      Top = 134
      Width = 21
      Height = 21
      TabOrder = 7
      OnClick = CEADataDownButtonClick
      Glyph.Data = {
        6A000000424D6A000000000000003E00000028000000090000000B0000000100
        0100000000002C0000000000000000000000020000000000000000000000FFFF
        FF00FF800000F7800000E3800000C180000080800000E3800000E3800000E380
        0000E3800000E3800000FF800000}
    end
  end
  object FormOKButton: TButton
    Left = 183
    Top = 829
    Width = 75
    Height = 23
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 8
  end
  object FormCancelButton: TButton
    Left = 264
    Top = 829
    Width = 75
    Height = 23
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 9
  end
  object StandardGroupBox: TGroupBox
    Left = 8
    Top = 347
    Width = 330
    Height = 164
    Caption = ' Standard resolutions '
    ParentBackground = False
    TabOrder = 6
    object StandardListBox: TListBox
      Left = 9
      Top = 19
      Width = 312
      Height = 108
      Style = lbOwnerDrawFixed
      Columns = 2
      ItemHeight = 13
      TabOrder = 0
      OnClick = StandardListBoxSelect
      OnDblClick = StandardListBoxDoubleClick
      OnDrawItem = StandardListBoxDrawItem
      OnMouseDown = StandardListBoxClick
    end
    object StandardAddButton: TButton
      Left = 8
      Top = 134
      Width = 42
      Height = 21
      Caption = 'Add...'
      TabOrder = 1
      OnClick = StandardAddButtonClick
    end
    object StandardEditButton: TButton
      Left = 50
      Top = 134
      Width = 42
      Height = 21
      Caption = 'Edit...'
      TabOrder = 2
      OnClick = StandardEditButtonClick
    end
    object StandardDeleteButton: TButton
      Left = 92
      Top = 134
      Width = 42
      Height = 21
      Caption = 'Delete'
      TabOrder = 3
      OnClick = StandardDeleteButtonClick
    end
    object StandardDeleteAllButton: TButton
      Left = 134
      Top = 134
      Width = 56
      Height = 21
      Caption = 'Delete all'
      TabOrder = 4
      OnClick = StandardDeleteAllButtonClick
    end
    object StandardResetButton: TButton
      Left = 190
      Top = 134
      Width = 42
      Height = 21
      Caption = 'Reset'
      TabOrder = 5
      OnClick = StandardResetButtonClick
    end
    object StandardUpButton: TBitBtn
      Left = 280
      Top = 134
      Width = 21
      Height = 21
      TabOrder = 6
      OnClick = StandardUpButtonClick
      Glyph.Data = {
        6A000000424D6A000000000000003E00000028000000090000000B0000000100
        0100000000002C0000000000000000000000020000000000000000000000FFFF
        FF00FF800000E3800000E3800000E3800000E3800000E380000080800000C180
        0000E3800000F7800000FF800000}
    end
    object StandardDownButton: TBitBtn
      Left = 301
      Top = 134
      Width = 21
      Height = 21
      TabOrder = 7
      OnClick = StandardDownButtonClick
      Glyph.Data = {
        6A000000424D6A000000000000003E00000028000000090000000B0000000100
        0100000000002C0000000000000000000000020000000000000000000000FFFF
        FF00FF800000F7800000E3800000C180000080800000E3800000E3800000E380
        0000E3800000E3800000FF800000}
    end
  end
  object DIDDataGroupBox: TGroupBox
    Left = 8
    Top = 516
    Width = 330
    Height = 307
    Caption = ' Data blocks '
    ParentBackground = False
    TabOrder = 7
    object DIDDataListBox: TListBox
      Left = 9
      Top = 19
      Width = 312
      Height = 251
      Style = lbOwnerDrawFixed
      ItemHeight = 13
      TabOrder = 0
      OnClick = DIDDataListBoxSelect
      OnDblClick = DIDDataListBoxDoubleClick
      OnDrawItem = DIDDataListBoxDrawItem
      OnMouseDown = DIDDataListBoxClick
    end
    object DIDDataAddButton: TButton
      Left = 8
      Top = 277
      Width = 42
      Height = 21
      Caption = 'Add...'
      TabOrder = 1
      OnClick = DIDDataAddButtonClick
    end
    object DIDDataEditButton: TButton
      Left = 50
      Top = 277
      Width = 42
      Height = 21
      Caption = 'Edit...'
      TabOrder = 2
      OnClick = DIDDataEditButtonClick
    end
    object DIDDataDeleteButton: TButton
      Left = 92
      Top = 277
      Width = 42
      Height = 21
      Caption = 'Delete'
      TabOrder = 3
      OnClick = DIDDataDeleteButtonClick
    end
    object DIDDataDeleteAllButton: TButton
      Left = 134
      Top = 277
      Width = 56
      Height = 21
      Caption = 'Delete all'
      TabOrder = 4
      OnClick = DIDDataDeleteAllButtonClick
    end
    object DIDDataResetButton: TButton
      Left = 190
      Top = 277
      Width = 42
      Height = 21
      Caption = 'Reset'
      TabOrder = 5
      OnClick = DIDDataResetButtonClick
    end
    object DIDDataUpButton: TBitBtn
      Left = 280
      Top = 277
      Width = 21
      Height = 21
      TabOrder = 6
      OnClick = DIDDataUpButtonClick
      Glyph.Data = {
        6A000000424D6A000000000000003E00000028000000090000000B0000000100
        0100000000002C0000000000000000000000020000000000000000000000FFFF
        FF00FF800000E3800000E3800000E3800000E3800000E380000080800000C180
        0000E3800000F7800000FF800000}
    end
    object DIDDataDownButton: TBitBtn
      Left = 301
      Top = 277
      Width = 21
      Height = 21
      TabOrder = 7
      OnClick = DIDDataDownButtonClick
      Glyph.Data = {
        6A000000424D6A000000000000003E00000028000000090000000B0000000100
        0100000000002C0000000000000000000000020000000000000000000000FFFF
        FF00FF800000F7800000E3800000C180000080800000E3800000E3800000E380
        0000E3800000E3800000FF800000}
    end
  end
end
