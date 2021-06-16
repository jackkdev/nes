start:
  jsr init

loop:
  jsr drawMap ; fuck fuck fuck
  jsr genMap
  jmp loop