object DisplayForm: TDisplayForm
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Custom Resolution Utility 1.3.99-p1 by ToastyX'
  ClientHeight = 456
  ClientWidth = 496
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object DisplayComboBox: TComboBox
    Left = 8
    Top = 8
    Width = 306
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 0
    OnChange = DisplayComboBoxChange
  end
  object DisplayEditButton: TButton
    Left = 321
    Top = 8
    Width = 42
    Height = 21
    Caption = 'Edit...'
    TabOrder = 1
    OnClick = DisplayEditButtonClick
  end
  object DisplayCopyButton: TButton
    Left = 363
    Top = 8
    Width = 42
    Height = 21
    Caption = 'Copy'
    TabOrder = 2
    OnClick = DisplayCopyButtonClick
  end
  object DisplayPasteButton: TButton
    Left = 405
    Top = 8
    Width = 42
    Height = 21
    Caption = 'Paste'
    TabOrder = 3
    OnClick = DisplayPasteButtonClick
  end
  object DisplayDeleteButton: TButton
    Left = 447
    Top = 8
    Width = 42
    Height = 21
    Caption = 'Delete'
    TabOrder = 4
    OnClick = DisplayDeleteButtonClick
  end
  object EstablishedGroupBox: TGroupBox
    Left = 8
    Top = 35
    Width = 142
    Height = 385
    Caption = ' Established resolutions '
    ParentBackground = False
    TabOrder = 5
    object EstablishedLabel1: TLabel
      Left = 33
      Top = 21
      Width = 68
      Height = 14
      Caption = '640x480 (4:3)'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object EstablishedLabel2: TLabel
      Left = 33
      Top = 111
      Width = 68
      Height = 14
      Caption = '800x600 (4:3)'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object EstablishedLabel3: TLabel
      Left = 33
      Top = 221
      Width = 74
      Height = 14
      Caption = '1024x768 (4:3)'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object EstablishedLabel4: TLabel
      Left = 33
      Top = 311
      Width = 80
      Height = 14
      Caption = '1280x1024 (5:4)'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object EstablishedCheckBox2: TCheckBox
      Tag = 2
      Left = 9
      Top = 39
      Width = 103
      Height = 17
      Caption = '640x480 @ 60 Hz'
      TabOrder = 0
      OnClick = EstablishedCheckBoxClick
    end
    object EstablishedCheckBox4: TCheckBox
      Tag = 4
      Left = 9
      Top = 59
      Width = 103
      Height = 17
      Caption = '640x480 @ 72 Hz'
      TabOrder = 1
      OnClick = EstablishedCheckBoxClick
    end
    object EstablishedCheckBox5: TCheckBox
      Tag = 5
      Left = 9
      Top = 79
      Width = 103
      Height = 17
      Caption = '640x480 @ 75 Hz'
      TabOrder = 2
      OnClick = EstablishedCheckBoxClick
    end
    object EstablishedCheckBox6: TCheckBox
      Tag = 6
      Left = 9
      Top = 129
      Width = 103
      Height = 17
      Caption = '800x600 @ 56 Hz'
      TabOrder = 3
      OnClick = EstablishedCheckBoxClick
    end
    object EstablishedCheckBox7: TCheckBox
      Tag = 7
      Left = 9
      Top = 149
      Width = 103
      Height = 17
      Caption = '800x600 @ 60 Hz'
      TabOrder = 4
      OnClick = EstablishedCheckBoxClick
    end
    object EstablishedCheckBox8: TCheckBox
      Tag = 8
      Left = 9
      Top = 169
      Width = 103
      Height = 17
      Caption = '800x600 @ 72 Hz'
      TabOrder = 5
      OnClick = EstablishedCheckBoxClick
    end
    object EstablishedCheckBox9: TCheckBox
      Tag = 9
      Left = 9
      Top = 189
      Width = 103
      Height = 17
      Caption = '800x600 @ 75 Hz'
      TabOrder = 6
      OnClick = EstablishedCheckBoxClick
    end
    object EstablishedCheckBox12: TCheckBox
      Tag = 12
      Left = 9
      Top = 239
      Width = 109
      Height = 17
      Caption = '1024x768 @ 60 Hz'
      TabOrder = 7
      OnClick = EstablishedCheckBoxClick
    end
    object EstablishedCheckBox13: TCheckBox
      Tag = 13
      Left = 9
      Top = 259
      Width = 109
      Height = 17
      Caption = '1024x768 @ 70 Hz'
      TabOrder = 8
      OnClick = EstablishedCheckBoxClick
    end
    object EstablishedCheckBox14: TCheckBox
      Tag = 14
      Left = 9
      Top = 279
      Width = 109
      Height = 17
      Caption = '1024x768 @ 75 Hz'
      TabOrder = 9
      OnClick = EstablishedCheckBoxClick
    end
    object EstablishedCheckBox15: TCheckBox
      Tag = 15
      Left = 9
      Top = 329
      Width = 115
      Height = 17
      Caption = '1280x1024 @ 75 Hz'
      TabOrder = 10
      OnClick = EstablishedCheckBoxClick
    end
    object EstablishedAllButton: TButton
      Left = 8
      Top = 355
      Width = 42
      Height = 21
      Caption = 'All'
      TabOrder = 11
      OnClick = EstablishedAllButtonClick
    end
    object EstablishedNoneButton: TButton
      Left = 50
      Top = 355
      Width = 42
      Height = 21
      Caption = 'None'
      TabOrder = 12
      OnClick = EstablishedNoneButtonClick
    end
    object EstablishedResetButton: TButton
      Left = 92
      Top = 355
      Width = 42
      Height = 21
      Caption = 'Reset'
      TabOrder = 13
      OnClick = EstablishedResetButtonClick
    end
  end
  object DetailedGroupBox: TGroupBox
    Left = 158
    Top = 35
    Width = 330
    Height = 112
    Caption = ' Detailed resolutions '
    ParentBackground = False
    TabOrder = 6
    object DetailedListBox: TListBox
      Left = 9
      Top = 19
      Width = 312
      Height = 56
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
      Top = 82
      Width = 42
      Height = 21
      Caption = 'Add...'
      TabOrder = 1
      OnClick = DetailedAddButtonClick
    end
    object DetailedEditButton: TButton
      Left = 50
      Top = 82
      Width = 42
      Height = 21
      Caption = 'Edit...'
      TabOrder = 2
      OnClick = DetailedEditButtonClick
    end
    object DetailedDeleteButton: TButton
      Left = 92
      Top = 82
      Width = 42
      Height = 21
      Caption = 'Delete'
      TabOrder = 3
      OnClick = DetailedDeleteButtonClick
    end
    object DetailedDeleteAllButton: TButton
      Left = 134
      Top = 82
      Width = 56
      Height = 21
      Caption = 'Delete all'
      TabOrder = 4
      OnClick = DetailedDeleteAllButtonClick
    end
    object DetailedResetButton: TButton
      Left = 190
      Top = 82
      Width = 42
      Height = 21
      Caption = 'Reset'
      TabOrder = 5
      OnClick = DetailedResetButtonClick
    end
    object DetailedUpButton: TBitBtn
      Left = 280
      Top = 82
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
      Top = 82
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
  object StandardGroupBox: TGroupBox
    Left = 158
    Top = 152
    Width = 330
    Height = 164
    Caption = ' Standard resolutions '
    ParentBackground = False
    TabOrder = 7
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
  object DisplayImportButton: TButton
    Left = 7
    Top = 426
    Width = 69
    Height = 23
    Caption = 'Import...'
    TabOrder = 9
    OnClick = DisplayImportButtonClick
  end
  object DisplayExportButton: TButton
    Left = 82
    Top = 426
    Width = 69
    Height = 23
    Caption = 'Export...'
    TabOrder = 10
    OnClick = DisplayExportButtonClick
  end
  object FormOKButton: TButton
    Left = 333
    Top = 426
    Width = 75
    Height = 23
    Caption = 'OK'
    Default = True
    TabOrder = 11
    OnClick = FormOKButtonClick
  end
  object FormCancelButton: TButton
    Left = 414
    Top = 426
    Width = 75
    Height = 23
    Cancel = True
    Caption = 'Cancel'
    TabOrder = 12
    OnClick = FormCancelButtonClick
  end
  object ExtensionGroupBox: TGroupBox
    Left = 158
    Top = 321
    Width = 330
    Height = 99
    Caption = ' Extension blocks '
    ParentBackground = False
    TabOrder = 8
    object ExtensionListBox: TListBox
      Left = 9
      Top = 19
      Width = 312
      Height = 43
      Style = lbOwnerDrawFixed
      ItemHeight = 13
      TabOrder = 0
      OnClick = ExtensionListBoxSelect
      OnDblClick = ExtensionListBoxDoubleClick
      OnDrawItem = ExtensionListBoxDrawItem
      OnMouseDown = ExtensionListBoxClick
    end
    object ExtensionAddButton: TButton
      Left = 8
      Top = 69
      Width = 42
      Height = 21
      Caption = 'Add...'
      TabOrder = 1
      OnClick = ExtensionAddButtonClick
    end
    object ExtensionEditButton: TButton
      Left = 50
      Top = 69
      Width = 42
      Height = 21
      Caption = 'Edit...'
      TabOrder = 2
      OnClick = ExtensionEditButtonClick
    end
    object ExtensionDeleteButton: TButton
      Left = 92
      Top = 69
      Width = 42
      Height = 21
      Caption = 'Delete'
      TabOrder = 3
      OnClick = ExtensionDeleteButtonClick
    end
    object ExtensionDeleteAllButton: TButton
      Left = 134
      Top = 69
      Width = 56
      Height = 21
      Caption = 'Delete all'
      TabOrder = 4
      OnClick = ExtensionDeleteAllButtonClick
    end
    object ExtensionResetButton: TButton
      Left = 190
      Top = 69
      Width = 42
      Height = 21
      Caption = 'Reset'
      TabOrder = 5
      OnClick = ExtensionResetButtonClick
    end
    object ExtensionUpButton: TBitBtn
      Left = 280
      Top = 69
      Width = 21
      Height = 21
      TabOrder = 6
      OnClick = ExtensionUpButtonClick
      Glyph.Data = {
        6A000000424D6A000000000000003E00000028000000090000000B0000000100
        0100000000002C0000000000000000000000020000000000000000000000FFFF
        FF00FF800000E3800000E3800000E3800000E3800000E380000080800000C180
        0000E3800000F7800000FF800000}
    end
    object ExtensionDownButton: TBitBtn
      Left = 301
      Top = 69
      Width = 21
      Height = 21
      TabOrder = 7
      OnClick = ExtensionDownButtonClick
      Glyph.Data = {
        6A000000424D6A000000000000003E00000028000000090000000B0000000100
        0100000000002C0000000000000000000000020000000000000000000000FFFF
        FF00FF800000F7800000E3800000C180000080800000E3800000E3800000E380
        0000E3800000E3800000FF800000}
    end
  end
end
