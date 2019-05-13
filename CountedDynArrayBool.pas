{-------------------------------------------------------------------------------

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

-------------------------------------------------------------------------------}
{===============================================================================

  Counted dynamic arrays

    Counted dynamic array of Boolean values

  ©František Milt 2019-05-13

  Version 1.1.0

  Dependencies:
    AuxTypes    - github.com/TheLazyTomcat/Lib.AuxTypes
    ListSorters - github.com/TheLazyTomcat/Lib.ListSorters

===============================================================================}
unit CountedDynArrayBool;

{$INCLUDE '.\CountedDynArrays_defs.inc'}

interface

uses
  AuxTypes,
  CountedDynArrays;

type
  TCDABaseType = Boolean;
  PCDABaseType = ^TCDABaseType;

  TCountedDynArrayBoolean = record
    Arr:    array of TCDABaseType;
    SigA:   UInt32;
    Count:  Integer;
    Data:   PtrInt;
    SigB:   UInt32;
  end;
  PCountedDynArrayBoolean = ^TCountedDynArrayBoolean;

  TBooleanCountedDynArray = TCountedDynArrayBoolean;
  PBooleanCountedDynArray = PCountedDynArrayBoolean;

  TCDAArrayType = TCountedDynArrayBoolean;
  PCDAArrayType = PCountedDynArrayBoolean;

{$DEFINE CDA_Interface}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Interface}

implementation

uses
  SysUtils,
  ListSorters;

{$IFDEF FPC_DisableWarns}
  {$DEFINE FPCDWM}
  {$DEFINE W5024:={$WARN 5024 OFF}} // Parameter "$1" not used  
  {$PUSH}{$WARN 2005 OFF} // Comment level $1 found
  {$IF Defined(FPC) and (FPC_FULLVERSION >= 30000)}
    {$DEFINE W5093:={$WARN 5093 OFF}} // Function result variable of a managed type does not seem to initialized
    {$DEFINE W5094:={$WARN 5094 OFF}} // Function result variable of a managed type does not seem to initialized
    {$DEFINE W5060:=}
  {$ELSE}
    {$DEFINE W5093:=}
    {$DEFINE W5094:=}
    {$DEFINE W5060:={$WARN 5060 OFF}} // Function result variable does not seem to be initialized
  {$IFEND}
  {$POP}
{$ENDIF}

Function CDA_CompareFunc(A,B: TCDABaseType): Integer; {$IFDEF CanInline} inline; {$ENDIF}
begin
Result := Abs(Ord(B)) - Abs(Ord(A));
end;

//------------------------------------------------------------------------------

{$DEFINE CDA_Implementation}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Implementation}

end.
