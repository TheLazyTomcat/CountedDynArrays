{-------------------------------------------------------------------------------

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

-------------------------------------------------------------------------------}
{===============================================================================

  Counted Dynamic Arrays

    Counted dynamic array of Variant values

  Version 1.2.2 (2019-09-22)
  
  Last changed 2019-10-10

  ©2018-2019 František Milt

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
    AuxTypes    - github.com/TheLazyTomcat/Lib.AuxTypes
    AuxClasses  - github.com/TheLazyTomcat/Lib.AuxClasses
    ListSorters - github.com/TheLazyTomcat/Lib.ListSorters
    StrRect     - github.com/TheLazyTomcat/Lib.StrRect

===============================================================================}
unit CountedDynArrayVariant;

{$INCLUDE '.\CountedDynArrays_defs.inc'}

{$DEFINE CDA_ConstBaseType}

{$DEFINE CDA_FuncOverride_ItemCompare}

interface

uses
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

  // aliases
  TCountedDynArrayOfVariant = TCountedDynArrayVariant;
  PCountedDynArrayOfVariant = PCountedDynArrayVariant;

  TVariantCountedDynArray = TCountedDynArrayVariant;
  PVariantCountedDynArray = PCountedDynArrayVariant;

  TCDAArrayType = TCountedDynArrayVariant;
  PCDAArrayType = PCountedDynArrayVariant;

{$DEFINE CDA_Interface}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Interface}

implementation

uses
  SysUtils, Variants,
  ListSorters;

{$INCLUDE '.\CountedDynArrays_msgdis.inc'}

Function CDA_ItemCompare(const A,B: TCDABaseType): Integer;{$IFDEF CanInline} inline;{$ENDIF}
begin
case VarCompareValue(A,B) of
  vrEqual:        Result := 0;
  vrLessThan:     Result := -1;
  vrGreaterThan:  Result := +1;
  vrNotEqual:     Result := 0;
else
  Result := 0;
end;
end;

{$DEFINE CDA_Implementation}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Implementation}

end.

