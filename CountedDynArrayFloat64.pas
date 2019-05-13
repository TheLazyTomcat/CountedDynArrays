{-------------------------------------------------------------------------------

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

-------------------------------------------------------------------------------}
{===============================================================================

  Counted dynamic arrays

    Counted dynamic array of Float64 (Double) values

  ©František Milt 2019-05-13

  Version 1.1.0

  Dependencies:
    AuxTypes    - github.com/TheLazyTomcat/Lib.AuxTypes
    ListSorters - github.com/TheLazyTomcat/Lib.ListSorters

===============================================================================}
unit CountedDynArrayFloat64;

{$INCLUDE '.\CountedDynArrays_defs.inc'}

interface

uses
  AuxTypes,
  CountedDynArrays;

type
  TCDABaseType = Float64;
  PCDABaseType = ^TCDABaseType;

  TFloat64CountedDynArray = record
    Arr:    array of TCDABaseType;
    SigA:   UInt32;
    Count:  Integer;
    Data:   PtrInt;
    SigB:   UInt32;
  end;
  PFloat64CountedDynArray = ^TFloat64CountedDynArray;

  TCDAArrayType = TFloat64CountedDynArray;
  PCDAArrayType = PFloat64CountedDynArray;

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

Function CDA_CompareFunc(A,B: TCDABaseType): Integer;
begin
If A > B then Result := -1
  else If A < B then Result := 1
    else Result := 0;
end;

//------------------------------------------------------------------------------

{$DEFINE CDA_Implementation}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Implementation}

end.

