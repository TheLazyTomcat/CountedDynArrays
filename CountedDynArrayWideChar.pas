{-------------------------------------------------------------------------------

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

-------------------------------------------------------------------------------}
{===============================================================================

  Counted Dynamic Arrays

    Counted dynamic array of WideChar values

  �Franti�ek Milt 2019-08-14

  Version 1.2.0

  Contacts:
    Franti�ek Milt: frantisek.milt@gmail.com

  Support:
    If you find this code useful, please consider supporting its author(s) by
    making a small donation using the following link(s):

      https://www.paypal.me/FMilt

  Dependencies:
    AuxTypes    - github.com/TheLazyTomcat/Lib.AuxTypes
    AuxClasses  - github.com/TheLazyTomcat/Lib.AuxClasses
    ListSorters - github.com/TheLazyTomcat/Lib.ListSorters
    StrRect     - github.com/TheLazyTomcat/Lib.StrRect

===============================================================================}
unit CountedDynArrayWideChar;

{$INCLUDE '.\CountedDynArrays_defs.inc'}

{$DEFINE CDA_CaseSensitiveBaseType}

{$DEFINE CDA_FuncOverride_ItemCompare}

interface

uses
  AuxTypes,
  CountedDynArrays;

type
  TCDABaseType = WideChar;
  PCDABaseType = ^TCDABaseType;

  TCountedDynArrayWideChar = record
  {$DEFINE CDA_Structure}
    {$INCLUDE '.\CountedDynArrays.inc'}
  {$UNDEF CDA_Structure}
  end;
  PCountedDynArrayWideChar = ^TCountedDynArrayWideChar;

  // aliases
  TCountedDynArrayOfWideChar = TCountedDynArrayWideChar;
  PCountedDynArrayOfWideChar = PCountedDynArrayWideChar;

  TWideCharCountedDynArray = TCountedDynArrayWideChar;
  PWideCharCountedDynArray = PCountedDynArrayWideChar;

  TCDAArrayType = TCountedDynArrayWideChar;
  PCDAArrayType = PCountedDynArrayWideChar;

{$DEFINE CDA_Interface}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Interface}

implementation

uses
  SysUtils,
  ListSorters, StrRect;

{$INCLUDE '.\CountedDynArrays_msgdis.inc'}

Function CDA_ItemCompare(const A,B: TCDABaseType; CaseSensitive: Boolean): Integer;{$IFDEF CanInline} inline;{$ENDIF}
begin
Result := -WideStringCompare(A,B,CaseSensitive);
end;

//------------------------------------------------------------------------------

{$DEFINE CDA_Implementation}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Implementation}

end.
