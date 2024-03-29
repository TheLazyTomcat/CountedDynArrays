{-------------------------------------------------------------------------------

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

-------------------------------------------------------------------------------}
{===============================================================================

  Counted Dynamic Arrays

    Counted dynamic array of UTF8String values

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
unit CountedDynArrayUTF8String;

{$INCLUDE '.\CountedDynArrays_defs.inc'}

{$DEFINE CDA_ConstBaseType}
{$DEFINE CDA_CaseSensitiveBaseType}

{$DEFINE CDA_FuncOverride_ItemUnique}
{$DEFINE CDA_FuncOverride_ItemCompare}
{$DEFINE CDA_FuncOverride_ItemWrite}
{$DEFINE CDA_FuncOverride_ItemRead}

interface

uses
  Classes,
  AuxTypes,
  CountedDynArrays;

type
  TCDABaseType = UTF8String;
  PCDABaseType = ^TCDABaseType;

  TCountedDynArrayUTF8String = record
  {$DEFINE CDA_Structure}
    {$INCLUDE '.\CountedDynArrays.inc'}
  {$UNDEF CDA_Structure}
  end;
  PCountedDynArrayUTF8String = ^TCountedDynArrayUTF8String;

  TCDAArrayType = TCountedDynArrayUTF8String;
  PCDAArrayType = PCountedDynArrayUTF8String;

  // aliases
  TCountedDynArrayOfUTF8String = TCountedDynArrayUTF8String;
  PCountedDynArrayOfUTF8String = PCountedDynArrayUTF8String;

  TUTF8StringCountedDynArray = TCountedDynArrayUTF8String;
  PUTF8StringCountedDynArray = PCountedDynArrayUTF8String;

  TCDAOfUTF8String = TCountedDynArrayUTF8String;
  PCDAOfUTF8String = PCountedDynArrayUTF8String;

  TCDAUTF8String = TCountedDynArrayUTF8String;
  PCDAUTF8String = PCountedDynArrayUTF8String;

  TUTF8StringCDA = TCountedDynArrayUTF8String;
  PUTF8StringCDA = PCountedDynArrayUTF8String;

{$DEFINE CDA_Interface}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Interface}

implementation

uses
  SysUtils,
  ListSorters, StrRect, BinaryStreaming;

{$INCLUDE '.\CountedDynArrays_msgdis.inc'}

const
  CDA_DEFAULT_VALUE = TCDABaseType('');

  CDA_ARRAY_NAME = 'AoUTF8String';

//------------------------------------------------------------------------------

procedure CDA_ItemUnique(var Item: TCDABaseType);{$IFDEF CanInline} inline;{$ENDIF}
begin
UniqueString({$IFNDEF FPC}AnsiString{$ENDIF}(Item));
end;

//------------------------------------------------------------------------------

Function CDA_ItemCompare(const A,B: TCDABaseType; CaseSensitive: Boolean): Integer;{$IFDEF CanInline} inline;{$ENDIF}
begin
Result := UTF8StringCompare(A,B,CaseSensitive);
end;

//------------------------------------------------------------------------------

procedure CDA_ItemWrite(const Item: TCDABaseType; Stream: TStream);
begin
Stream_WriteUTF8String(Stream,Item);
end;

//------------------------------------------------------------------------------

Function CDA_ItemRead(Stream: TStream): TCDABaseType;
begin
Result := Stream_GetUTF8String(Stream);
end;

//------------------------------------------------------------------------------

{$DEFINE CDA_Implementation}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Implementation}

end.
