{-------------------------------------------------------------------------------

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

-------------------------------------------------------------------------------}
{===============================================================================

  Counted Dynamic Arrays

    Counted dynamic array of AnsiChar values

  Version 1.2.2 (2019-09-22)
  
  Last changed 2019-09-22

  ©2018-2019 František Milt

  Contacts:
    František Milt: frantisek.milt@gmail.com

  Support:
    If you find this code useful, please consider supporting its author(s) by
    making a small donation using the following link(s):

      https://www.paypal.me/FMilt

  Changelog:
    For detailed changelog and history please refer to this git repository:

      github.com/TheLazyTomcat/Lib.AuxClasses

  Dependencies:
    AuxTypes    - github.com/TheLazyTomcat/Lib.AuxTypes
    AuxClasses  - github.com/TheLazyTomcat/Lib.AuxClasses    
    ListSorters - github.com/TheLazyTomcat/Lib.ListSorters
    StrRect     - github.com/TheLazyTomcat/Lib.StrRect

===============================================================================}
unit CountedDynArrayAnsiChar;

{$INCLUDE '.\CountedDynArrays_defs.inc'}

{$DEFINE CDA_CaseSensitiveBaseType}

{$DEFINE CDA_FuncOverride_ItemCompare}

interface

uses
  AuxTypes,
  CountedDynArrays;

type
  TCDABaseType = AnsiChar;
  PCDABaseType = ^TCDABaseType;

  TCountedDynArrayAnsiChar = record
  {$DEFINE CDA_Structure}
    {$INCLUDE '.\CountedDynArrays.inc'}
  {$UNDEF CDA_Structure}
  end;
  PCountedDynArrayAnsiChar = ^TCountedDynArrayAnsiChar;

  // aliases
  TCountedDynArrayOfAnsiChar = TCountedDynArrayAnsiChar;
  PCountedDynArrayOfAnsiChar = PCountedDynArrayAnsiChar;

  TAnsiCharCountedDynArray = TCountedDynArrayAnsiChar;
  PAnsiCharCountedDynArray = PCountedDynArrayAnsiChar;

  TCDAArrayType = TCountedDynArrayAnsiChar;
  PCDAArrayType = PCountedDynArrayAnsiChar;

{$DEFINE CDA_Interface}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Interface}

implementation

uses
  SysUtils,
  ListSorters,StrRect;

{$INCLUDE '.\CountedDynArrays_msgdis.inc'}

Function CDA_ItemCompare(const A,B: TCDABaseType; CaseSensitive: Boolean): Integer;{$IFDEF CanInline} inline;{$ENDIF}
begin
Result := AnsiStringCompare(A,B,CaseSensitive);
end;

//------------------------------------------------------------------------------

{$DEFINE CDA_Implementation}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Implementation}

end.
