{-------------------------------------------------------------------------------

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

-------------------------------------------------------------------------------}
{===============================================================================

  Counted Dynamic Arrays

    Counted dynamic array of ShortString values

  Version 1.4.1 (2023-01-27)

  Last changed 2023-09-04

  ©2018-2023 František Milt

  Contacts:
    František Milt: frantisek.milt@gmail.com

  Support:
    If you find this code useful, please consider supporting its author(s) by
    making a small donation using the following link(s):

      https://www.paypal.me/FMilt

  Changelog:
    For detailed changelog and history please refer to this git repository:

      github.com/TheLazyTomcat/CountedDynArrays

  Dependencies:
    AuxClasses      - github.com/TheLazyTomcat/Lib.AuxClasses
    AuxTypes        - github.com/TheLazyTomcat/Lib.AuxTypes
    BinaryStreaming - github.com/TheLazyTomcat/Lib.BinaryStreaming
    ListSorters     - github.com/TheLazyTomcat/Lib.ListSorters
    StrRect         - github.com/TheLazyTomcat/Lib.StrRect

===============================================================================}
unit CountedDynArrayShortString;

{$INCLUDE '.\CountedDynArrays_defs.inc'}

{$DEFINE CDA_ConstBaseType}
{$DEFINE CDA_CaseSensitiveBaseType}

{$DEFINE CDA_FuncOverride_ItemCompare}
{$DEFINE CDA_FuncOverride_ItemWrite}
{$DEFINE CDA_FuncOverride_ItemRead}

interface

uses
  Classes,
  AuxTypes,
  CountedDynArrays;

type
  TCDABaseType = ShortString;
  PCDABaseType = ^TCDABaseType;

  TCountedDynArrayShortString = record
  {$DEFINE CDA_Structure}
    {$INCLUDE '.\CountedDynArrays.inc'}
  {$UNDEF CDA_Structure}
  end;
  PCountedDynArrayShortString = ^TCountedDynArrayShortString;

  TCDAArrayType = TCountedDynArrayShortString;
  PCDAArrayType = PCountedDynArrayShortString;

  // aliases
  TCountedDynArrayOfShortString = TCountedDynArrayShortString;
  PCountedDynArrayOfShortString = PCountedDynArrayShortString;

  TShortStringCountedDynArray = TCountedDynArrayShortString;
  PShortStringCountedDynArray = PCountedDynArrayShortString;

  TCDAOfShortString = TCountedDynArrayShortString;
  PCDAOfShortString = PCountedDynArrayShortString;

  TCDAShortString = TCountedDynArrayShortString;
  PCDAShortString = PCountedDynArrayShortString;

  TShortStringCDA = TCountedDynArrayShortString;
  PShortStringCDA = PCountedDynArrayShortString;

{$DEFINE CDA_Interface}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Interface}

implementation

uses 
  SysUtils,
  ListSorters, StrRect, BinaryStreaming;

{$INCLUDE '.\CountedDynArrays_msgdis.inc'}

const
{$IFDEF FPC}
  CDA_DEFAULT_VALUE = TCDABaseType('');
{$ELSE}
  CDA_DEFAULT_VALUE: TCDABaseType = '';
{$ENDIF}

  CDA_ARRAY_NAME = 'AoShortString';

//------------------------------------------------------------------------------

Function CDA_ItemCompare(const A,B: TCDABaseType; CaseSensitive: Boolean): Integer;{$IFDEF CanInline} inline;{$ENDIF}
begin
Result := ShortStringCompare(A,B,CaseSensitive);
end;

//------------------------------------------------------------------------------

procedure CDA_ItemWrite(const Item: TCDABaseType; Stream: TStream);
begin
Stream_WriteShortString(Stream,Item);
end;

//------------------------------------------------------------------------------

Function CDA_ItemRead(Stream: TStream): TCDABaseType;
begin
Result := Stream_GetShortString(Stream);
end;

//------------------------------------------------------------------------------

{$DEFINE CDA_Implementation}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Implementation}

end.
