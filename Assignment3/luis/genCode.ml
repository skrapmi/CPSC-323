(* Project: Assignment 3 
   Members: Luis Gonzalez, Timothy Parks, Stephen Cordasco
*)

(*type definition*)
type id = string
and data_type = Int | Void
and var = Var of id * data_type
and func = Func of id * data_type * data_type
and args = expr list
and expr = 
    | Value of var
    | Call of func * args
    | Neq of expr * expr
    | Gt of expr * expr
    | Minus of expr * expr
and stmt =
    | Assign of var * expr 
    | Expr of expr
    | While of expr * stmt list
    | If of expr * stmt list * stmt list
and program = Program of stmt list ;; 

(*
* Class    : Register 
* Variable : rlist -  list that holds all the register 
* function : nextreg - returns  the next available register
*			   It does it by rotating the list and assigns it to rlist
*			   then returning the the origanal head of the list
* function : doneWreg - sorts the list and asigns it to rlist after registers are used
*			   at the end of a function or block
*)
class registers = object
  val mutable rlist = ["r1"; "r2"; "r3"; "r4"; "r5"; "r6"; "r7"; "r8"]
  method nextreg = match rlist with
    | [] -> ""
    |h::t -> (rlist <- (t @ [h])); h
  method doneWregs = 
    rlist <- (List.sort compare rlist);
end;;

(*Instance of registers *)
let reg = new registers;;

(*function : evaluates data type of variable, not used in program*)
let rec getdt = function
  |Void -> "void"
  |Int -> "int"
;; 

(*function : evalustes variable and prints the identifier of the variable*)
let varEval = function
    Var (vId, dt) ->  print_string vId
;;
(*
* function : expEval - evaluates an expression , only needs two 
*				regesters r1, r2 
*				it evalaluates by pattern matching with variant types 
*		        with exprec function
* variant  : Value - calls varEval
* variant  : Call - first matches with the function identifier with funcEval 
*		  function 
*		  if "getint" then its a simple print
*		  if "putint" first print some instructions then print 
*		  instructions involving arguments with the getArgs function
* variants : Neq, GT, Minus - all have simple prints for instructions
*)
let expEval  e  = 
  let r1 = reg#nextreg in 
  let r2 = reg#nextreg in
  let rec exprec = function
    | Value vVar -> varEval vVar 
    | Call (cf, cargs) -> 
        let funcEval = function
            Func (fid, fdta, fdtb) -> match fid with
            |"getint" -> 
                Printf.printf "a1 := &input\ncall readint\n";
            |"putint" -> 
                Printf.printf "a1 := &output\n";
                Printf.printf "%s := " r1;
                let rec getArgs = function
                  |[] -> ()
                  | h::t -> exprec h; getArgs t; 
                in getArgs cargs;  print_newline();
                  Printf.printf "a2 = %s \ncall writeint\n" r1
            | _ -> () ;
        in funcEval cf ;                   
    | Neq (ne, ne2) ->
        Printf.printf "\n%s := " r1; exprec ne ;
        Printf.printf "\n%s := " r2; exprec ne2 ; 
        Printf.printf "\n%s := %s != %s\n" r1 r1 r2;
    | Gt (ge, ge2) -> Printf.printf "%s := " r1; exprec ge ; 
        Printf.printf"\n%s := " r2; exprec ge2 ; 
        Printf.printf "\n%s = %s > %s\n" r1 r1 r2;
    | Minus (me, me2) -> Printf.printf "%s := " r1; exprec me ; 
        Printf.printf"\n%s := " r2; exprec me2; 
        Printf.printf "\n%s = %s - %s\n" r1 r1 r2;
  in exprec e; reg#doneWregs;
;;

(*
* function : codegen  - matches ast with variants in program 
*			  needs one register [r1]
* variant : Program - matches statement list with call to trav function 
*			with paramaters list of statement
*		        and integer label with intial value 
*		       of 1. Only while and if use labels
* variant : Assign - 1. evaluate the right hand side [rhs] expression  
*		     2. print the variables
*		     3. If its a function call print special variable rv
*		     4. make recursive call with tail and same label
* variant : Expr - call expEval and send expression te be evaluated
* variant : While - uses two labels 
*		   1. print "goto <label>" then the next label.
*		   2. print the body of the while which is made up of 
*		      a list of statements
*		   3. print the boolean expression 
*		   4. make recursive call with tail and label + 2
* variant : If - uses two labels
*		 1. print the boolean expression
*		 2. print the the else part
*		 3. print the body of the if statement
*		 4. make recursive call with tail and label + 2
*)
let codegen ast = 
  let r1 = reg#nextreg in
    match ast with
        Program stmtList -> Printf.printf "main: \n";
          let rec trav s label = match s with
            | [] -> ()
            | Assign(aVar, aExp)::t -> 
                expEval aExp ;
                (varEval aVar);
                Printf.printf" := %s \n" (match aExp with  
                                           | Call(x,y) -> "rv"
                                           | _ -> r1);
                trav t label;
            | Expr eExp::t ->  expEval eExp  ; 
                trav t label
            | While (wExp, wList)::t -> 
                Printf.printf "goto L%d\n" label;
                Printf.printf "L%d:\n" (label + 1); 
                trav wList (label + 2);  
                Printf.printf "L%d: " label; 
                expEval wExp ; 
                Printf.printf "if %s goto L%d\n" r1 (label + 1); 
                trav t label
            | If (ifExp, thenList, elseList)::t ->  
                expEval ifExp ; 
                Printf.printf "if %s goto L%d\n" r1 label; 
                trav elseList label; 
                Printf.printf "goto L%d\n" (label + 1); 
                Printf.printf "L%d:\n" (label);
                trav thenList label; 
                Printf.printf "L%d:\n" (label + 1); 
                trav t (label + 2)
          in trav stmtList 1; reg#doneWregs;
            Printf.printf "a1 := &output\ncall writeln\ngoto exit\n"
;;


(*function call with tree literal*)
codegen 
  (Program
     [Assign (Var ("i", Int), Call (Func ("getint", Void, Int), []));
      Assign (Var ("j", Int), Call (Func ("getint", Void, Int), []));
      While (Neq (Value (Var ("i", Int)), Value (Var ("j", Int))),
             [If (Gt (Value (Var ("i", Int)), Value (Var ("j", Int))),
                  [Assign (Var ("i", Int),
                           Minus (Value (Var ("i", Int)), 
                                  Value (Var ("j", Int))))],
                  [Assign (Var ("j", Int),
                           Minus (Value (Var ("j", Int)), 
                                  Value (Var ("i", Int))))])]);
      Expr (Call (Func ("putint", Int, Void), [Value (Var ("i", Int))]))]);;



