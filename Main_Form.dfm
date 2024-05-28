object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'I'#39'm dead inside'
  ClientHeight = 581
  ClientWidth = 746
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object Label1: TLabel
    Left = 24
    Top = 83
    Width = 57
    Height = 15
    Caption = 'File format'
  end
  object Label2: TLabel
    Left = 24
    Top = 27
    Width = 22
    Height = 15
    Caption = 'Disk'
  end
  object ComboBox1: TComboBox
    Left = 24
    Top = 104
    Width = 145
    Height = 23
    Style = csDropDownList
    TabOrder = 0
    Items.Strings = (
      'PDF'
      'JPG'
      'PNG')
  end
  object Button1: TButton
    Left = 24
    Top = 144
    Width = 145
    Height = 41
    Caption = 'Start search'
    TabOrder = 1
    OnClick = Button1Click
  end
  object ComboBox2: TComboBox
    Left = 24
    Top = 48
    Width = 145
    Height = 23
    Style = csDropDownList
    TabOrder = 2
  end
  object VirtualStringTree1: TVirtualStringTree
    Left = 208
    Top = 48
    Width = 361
    Height = 409
    AccessibleName = #1053#1086#1084#1077#1088' '#1082#1083#1072#1089#1090#1077#1088#1072
    DefaultNodeHeight = 19
    Header.AutoSizeIndex = 0
    Header.Options = [hoColumnResize, hoDrag, hoShowSortGlyphs, hoVisible]
    TabOrder = 3
    TreeOptions.PaintOptions = [toShowButtons, toShowDropmark, toShowHorzGridLines, toShowRoot, toShowTreeLines, toShowVertGridLines, toThemeAware, toUseBlendedImages, toFullVertGridLines]
    TreeOptions.SelectionOptions = [toFullRowSelect, toMultiSelect, toSelectNextNodeOnRemoval]
    OnGetText = VirtualStringTree1GetText
    Touch.InteractiveGestures = [igPan, igPressAndTap]
    Touch.InteractiveGestureOptions = [igoPanSingleFingerHorizontal, igoPanSingleFingerVertical, igoPanInertia, igoPanGutter, igoParentPassthrough]
    Columns = <
      item
        Position = 0
        Text = #1048#1076#1077#1085#1090#1080#1092#1080#1082#1072#1090#1086#1088
        Width = 101
      end
      item
        Position = 1
        Text = #1044#1080#1089#1082
        Width = 45
      end
      item
        Position = 2
        Text = #1056#1072#1089#1096#1080#1088#1077#1085#1080#1077
        Width = 90
      end
      item
        Position = 3
        Text = #1053#1086#1084#1077#1088' '#1082#1083#1072#1089#1090#1077#1088#1072
        Width = 111
      end>
  end
end
