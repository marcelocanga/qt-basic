       subroutine test2        
#include "common.h"   
c       INTEGER(C_INT)  ,BIND(C)  :: C_EXTERN
c       INTEGER(C_LONG) ,BIND(C,NAME='myVariable')  :: C2
 
c
c*********************************************      
c
       TYPE_INTEGER l
       l  = 4
       ll = 3
       write(*,*)'Hello from Fortran',sizeof(l)
       write(*,*)'Hello from Fortran'
       write(*,*)'Cool',l,ll
       write(*,*)'binding',rr,ss
       write(*,*)'Hello 2 from Fortran'
       return
       end
