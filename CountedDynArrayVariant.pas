{-------------------------------------------------------------------------------

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

-------------------------------------------------------------------------------}
{===============================================================================

  Counted Dynamic Arrays

    Counted dynamic array of Variant values

  Version 1.4.1 (2023-01-27)

  Last changed 2023-01-27

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
    AuxClasses         - github.com/TheLazyTomcat/Lib.AuxClasses
    AuxTypes           - github.com/TheLazyTomcat/Lib.AuxTypes
    BinaryStreaming    - github.com/TheLazyTomcat/Lib.BinaryStreaming
    ListSorters        - github.com/TheLazyTomcat/Lib.ListSorters
    StaticMemoryStream - github.com/TheLazyTomcat/Lib.StaticMemoryStream
    StrRect            - github.com/TheLazyTomcat/Lib.StrRect

===============================================================================}
unit CountedDynArrayVariant;

{$INCLUDE '.\CountedDynArrays_defs.inc'}

{$DEFINE CDA_ConstBaseType}

{$DEFINE CDA_FuncOverride_ItemCompare}
{$DEFINE CDA_FuncOverride_ItemWrite}
{$DEFINE CDA_FuncOverride_ItemRead}

interface

uses
  Classes,
  AuxTypes,
  CountedDynArrays;

type
  TCDABaseType = Variant;
  PCDABaseType = ^TCDABaseType;

  TCountedDynArrayVariant = record
  {$DEFINE CDA_Structure}
    {$INCLUDE '.\CountedDynArrays.inc'}
  {$UNDEF CDA_Structure}
  end;
  PCountedDynArrayVariant = ^TCountedDynArrayVariant;

  TCDAArrayType = TCountedDynArrayVariant;
  PCDAArrayType = PCountedDynArrayVariant;

  // aliases
  TCountedDynArrayOfVariant = TCountedDynArrayVariant;
  PCountedDynArrayOfVariant = PCountedDynArrayVariant;

  TVariantCountedDynArray = TCountedDynArrayVariant;
  PVariantCountedDynArray = PCountedDynArrayVariant;

  TCDAOfVariant = TCountedDynArrayVariant;
  PCDAOfVariant = PCountedDynArrayVariant;

  TCDAVariant = TCountedDynArrayVariant;
  PCDAVariant = PCountedDynArrayVariant;

  TVariantCDA = TCountedDynArrayVariant;
  PVariantCDA = PCountedDynArrayVariant;

{$DEFINE CDA_Interface}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Interface}

implementation

uses
  SysUtils, Variants,
  ListSorters, StrRect, BinaryStreaming;

{$INCLUDE '.\CountedDynArrays_msgdis.inc'}

const
  CDA_ARRAY_NAME = 'AoVariant';

//------------------------------------------------------------------------------  

Function CDA_DEFAULT_VALUE: Variant;{$IFDEF CanInline} inline;{$ENDIF}
begin
Result := NULL;
end;

//------------------------------------------------------------------------------

Function CDA_ItemCompare(const A,B: TCDABaseType): Integer;{$IFDEF CanInline} inline;{$ENDIF}
begin
case VarCompareValue(A,B) of
  vrEqual:        Result := 0;
  vrLessThan:     Result := -1;
  vrGreaterThan:  Result := +1;
  vrNotEqual:     Result := -1;   // preserve order
else
  Result := 0;
end;
end;

//------------------------------------------------------------------------------

procedure CDA_ItemWrite(const Item: TCDABaseType; Stream: TStream);
begin
Stream_WriteVariant(Stream,Item);
end;

//------------------------------------------------------------------------------

Function CDA_ItemRead(Stream: TStream): TCDABaseType;
begin
Result := Stream_ReadVariant(Stream);
end;

//------------------------------------------------------------------------------

{$DEFINE CDA_Implementation}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Implementation}

end.

