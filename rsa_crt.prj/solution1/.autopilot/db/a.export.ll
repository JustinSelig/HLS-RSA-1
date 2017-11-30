; ModuleID = '/home/jss459/Documents/ECE5770/HLS-RSA/rsa_crt.prj/solution1/.autopilot/db/a.o.2.bc'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@llvm_global_ctors_1 = appending global [1 x void ()*] [void ()* @_GLOBAL__I_a]
@llvm_global_ctors_0 = appending global [1 x i32] [i32 65535]
@dut_str = internal unnamed_addr constant [4 x i8] c"dut\00"
@ap_fifo_str = internal unnamed_addr constant [8 x i8] c"ap_fifo\00"
@p_str20 = internal unnamed_addr constant [1 x i8] zeroinitializer
@p_str19 = internal unnamed_addr constant [1 x i8] zeroinitializer
@p_str18 = internal unnamed_addr constant [1 x i8] zeroinitializer
@p_str17 = internal unnamed_addr constant [1 x i8] zeroinitializer
@p_str16 = internal unnamed_addr constant [1 x i8] zeroinitializer
@p_str15 = internal unnamed_addr constant [1 x i8] zeroinitializer
@p_str14 = internal unnamed_addr constant [1 x i8] zeroinitializer
@p_str13 = internal unnamed_addr constant [1 x i8] zeroinitializer
@p_str1 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@p_str = private unnamed_addr constant [3 x i8] c"L1\00", align 1

declare i32 @llvm.part.select.i32(i32, i32, i32) nounwind readnone

declare void @llvm.dbg.value(metadata, i64, metadata) nounwind readnone

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

define void @dut(i32* %strm_in_V_V, i32* %strm_out_V_V) {
  %tmp_V = alloca i32
  %empty = call i32 (...)* @_ssdm_op_SpecInterface(i32* %strm_out_V_V, [8 x i8]* @ap_fifo_str, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str17, [1 x i8]* @p_str18, [1 x i8]* @p_str19, i32 2, i32 2, i32 16, i32 16, [1 x i8]* @p_str20)
  %empty_6 = call i32 (...)* @_ssdm_op_SpecInterface(i32* %strm_in_V_V, [8 x i8]* @ap_fifo_str, i32 0, i32 0, i32 0, i32 0, [1 x i8]* @p_str13, [1 x i8]* @p_str14, [1 x i8]* @p_str15, i32 2, i32 2, i32 16, i32 16, [1 x i8]* @p_str16)
  call void (...)* @_ssdm_op_SpecBitsMap(i32* %strm_in_V_V), !map !65
  call void (...)* @_ssdm_op_SpecBitsMap(i32* %strm_out_V_V), !map !69
  call void (...)* @_ssdm_op_SpecTopModule([4 x i8]* @dut_str) nounwind
  %tmp_V_4 = call i32 @_ssdm_op_Read.ap_fifo.volatile.i32P(i32* %strm_in_V_V)
  %tmp_V_5 = call i32 @_ssdm_op_Read.ap_fifo.volatile.i32P(i32* %strm_in_V_V)
  %tmp_V_6 = call i32 @_ssdm_op_Read.ap_fifo.volatile.i32P(i32* %strm_in_V_V)
  store i32 1, i32* %tmp_V
  br label %1

; <label>:1                                       ; preds = %._crit_edge.i, %0
  %p_i = phi i32 [ %tmp_V_5, %0 ], [ %tmp, %._crit_edge.i ]
  %x_pn_i = phi i32 [ %tmp_V_4, %0 ], [ %tmp_6_i, %._crit_edge.i ]
  %tmp_i = icmp eq i32 %p_i, 0
  br i1 %tmp_i, label %power2.exit, label %2

; <label>:2                                       ; preds = %1
  %tmp_1 = trunc i32 %p_i to i1
  %x_assign_1 = urem i32 %x_pn_i, %tmp_V_6
  call void (...)* @_ssdm_op_SpecLoopName([3 x i8]* @p_str) nounwind
  %tmp_4_i = call i32 (...)* @_ssdm_op_SpecRegionBegin([3 x i8]* @p_str) nounwind
  call void (...)* @_ssdm_op_SpecLoopTripCount(i32 0, i32 32, i32 16, [1 x i8]* @p_str1) nounwind
  call void (...)* @_ssdm_op_SpecPipeline(i32 -1, i32 1, i32 1, i32 0, [1 x i8]* @p_str1) nounwind
  br i1 %tmp_1, label %3, label %._crit_edge.i

; <label>:3                                       ; preds = %2
  %tmp_V_load_1 = load i32* %tmp_V
  %tmp_3_i = mul i32 %x_assign_1, %tmp_V_load_1
  %res = urem i32 %tmp_3_i, %tmp_V_6
  store i32 %res, i32* %tmp_V
  br label %._crit_edge.i

._crit_edge.i:                                    ; preds = %3, %2
  %y_assign_1 = call i31 @_ssdm_op_PartSelect.i31.i32.i32.i32(i32 %p_i, i32 1, i32 31)
  %tmp = zext i31 %y_assign_1 to i32
  %tmp_6_i = mul i32 %x_assign_1, %x_assign_1
  %empty_7 = call i32 (...)* @_ssdm_op_SpecRegionEnd([3 x i8]* @p_str, i32 %tmp_4_i) nounwind
  br label %1

power2.exit:                                      ; preds = %1
  %tmp_V_load = load i32* %tmp_V
  call void @_ssdm_op_Write.ap_fifo.volatile.i32P(i32* %strm_out_V_V, i32 %tmp_V_load)
  ret void
}

define weak void @_ssdm_op_Write.ap_fifo.volatile.i32P(i32*, i32) {
entry:
  %empty = call i32 @_autotb_FifoWrite_i32(i32* %0, i32 %1)
  ret void
}

define weak void @_ssdm_op_SpecTopModule(...) {
entry:
  ret void
}

define weak i32 @_ssdm_op_SpecRegionEnd(...) {
entry:
  ret i32 0
}

define weak i32 @_ssdm_op_SpecRegionBegin(...) {
entry:
  ret i32 0
}

define weak void @_ssdm_op_SpecPipeline(...) nounwind {
entry:
  ret void
}

define weak void @_ssdm_op_SpecLoopTripCount(...) nounwind {
entry:
  ret void
}

define weak void @_ssdm_op_SpecLoopName(...) nounwind {
entry:
  ret void
}

define weak i32 @_ssdm_op_SpecInterface(...) {
entry:
  ret i32 0
}

define weak void @_ssdm_op_SpecBitsMap(...) {
entry:
  ret void
}

define weak i32 @_ssdm_op_Read.ap_fifo.volatile.i32P(i32*) {
entry:
  %empty = call i32 @_autotb_FifoRead_i32(i32* %0)
  ret i32 %empty
}

define weak i31 @_ssdm_op_PartSelect.i31.i32.i32.i32(i32, i32, i32) nounwind readnone {
entry:
  %empty = call i32 @llvm.part.select.i32(i32 %0, i32 %1, i32 %2)
  %empty_8 = trunc i32 %empty to i31
  ret i31 %empty_8
}

declare i1 @_ssdm_op_PartSelect.i1.i32.i32.i32(i32, i32, i32) nounwind readnone

declare i32 @_autotb_FifoWrite_i32(i32*, i32)

declare i32 @_autotb_FifoRead_i32(i32*)

declare void @_GLOBAL__I_a() nounwind section ".text.startup"

!opencl.kernels = !{!0, !0, !7, !10, !16, !18, !22, !26, !29, !32, !38, !40, !46, !46, !49, !49, !55, !49, !49, !49, !49}
!hls.encrypted.func = !{}
!llvm.map.gv = !{!58}

!0 = metadata !{null, metadata !1, metadata !2, metadata !3, metadata !4, metadata !5, metadata !6}
!1 = metadata !{metadata !"kernel_arg_addr_space", i32 0, i32 0}
!2 = metadata !{metadata !"kernel_arg_access_qual", metadata !"none", metadata !"none"}
!3 = metadata !{metadata !"kernel_arg_type", metadata !"hls::stream<bit32_t> &", metadata !"hls::stream<bit32_t> &"}
!4 = metadata !{metadata !"kernel_arg_type_qual", metadata !"", metadata !""}
!5 = metadata !{metadata !"kernel_arg_name", metadata !"strm_in", metadata !"strm_out"}
!6 = metadata !{metadata !"reqd_work_group_size", i32 1, i32 1, i32 1}
!7 = metadata !{null, metadata !1, metadata !2, metadata !8, metadata !4, metadata !9, metadata !6}
!8 = metadata !{metadata !"kernel_arg_type", metadata !"rsa_t", metadata !"rsa_t"}
!9 = metadata !{metadata !"kernel_arg_name", metadata !"a", metadata !"h"}
!10 = metadata !{null, metadata !11, metadata !12, metadata !13, metadata !14, metadata !15, metadata !6}
!11 = metadata !{metadata !"kernel_arg_addr_space", i32 0}
!12 = metadata !{metadata !"kernel_arg_access_qual", metadata !"none"}
!13 = metadata !{metadata !"kernel_arg_type", metadata !"rsa_t"}
!14 = metadata !{metadata !"kernel_arg_type_qual", metadata !""}
!15 = metadata !{metadata !"kernel_arg_name", metadata !"n"}
!16 = metadata !{null, metadata !1, metadata !2, metadata !8, metadata !4, metadata !17, metadata !6}
!17 = metadata !{metadata !"kernel_arg_name", metadata !"lower", metadata !"upper"}
!18 = metadata !{null, metadata !19, metadata !2, metadata !20, metadata !4, metadata !21, metadata !6}
!19 = metadata !{metadata !"kernel_arg_addr_space", i32 1, i32 1}
!20 = metadata !{metadata !"kernel_arg_type", metadata !"struct public_key*", metadata !"struct private_key*"}
!21 = metadata !{metadata !"kernel_arg_name", metadata !"pk", metadata !"sk"}
!22 = metadata !{null, metadata !23, metadata !2, metadata !24, metadata !4, metadata !25, metadata !6}
!23 = metadata !{metadata !"kernel_arg_addr_space", i32 0, i32 1}
!24 = metadata !{metadata !"kernel_arg_type", metadata !"rsa_t", metadata !"public_key_t*"}
!25 = metadata !{metadata !"kernel_arg_name", metadata !"plaintext", metadata !"pk"}
!26 = metadata !{null, metadata !23, metadata !2, metadata !27, metadata !4, metadata !28, metadata !6}
!27 = metadata !{metadata !"kernel_arg_type", metadata !"rsa_t", metadata !"private_key_t*"}
!28 = metadata !{metadata !"kernel_arg_name", metadata !"cyphertext", metadata !"sk"}
!29 = metadata !{null, metadata !1, metadata !2, metadata !30, metadata !4, metadata !31, metadata !6}
!30 = metadata !{metadata !"kernel_arg_type", metadata !"int", metadata !"int"}
!31 = metadata !{metadata !"kernel_arg_name", metadata !"base", metadata !"power"}
!32 = metadata !{null, metadata !33, metadata !34, metadata !35, metadata !36, metadata !37, metadata !6}
!33 = metadata !{metadata !"kernel_arg_addr_space", i32 0, i32 0, i32 0}
!34 = metadata !{metadata !"kernel_arg_access_qual", metadata !"none", metadata !"none", metadata !"none"}
!35 = metadata !{metadata !"kernel_arg_type", metadata !"rsa_t", metadata !"rsa_t", metadata !"rsa_t"}
!36 = metadata !{metadata !"kernel_arg_type_qual", metadata !"", metadata !"", metadata !""}
!37 = metadata !{metadata !"kernel_arg_name", metadata !"x", metadata !"y", metadata !"p"}
!38 = metadata !{null, metadata !1, metadata !2, metadata !8, metadata !4, metadata !39, metadata !6}
!39 = metadata !{metadata !"kernel_arg_name", metadata !"a", metadata !"b"}
!40 = metadata !{null, metadata !41, metadata !42, metadata !43, metadata !44, metadata !45, metadata !6}
!41 = metadata !{metadata !"kernel_arg_addr_space", i32 0, i32 0, i32 0, i32 0, i32 0, i32 0}
!42 = metadata !{metadata !"kernel_arg_access_qual", metadata !"none", metadata !"none", metadata !"none", metadata !"none", metadata !"none", metadata !"none"}
!43 = metadata !{metadata !"kernel_arg_type", metadata !"rsa_t", metadata !"rsa_t", metadata !"rsa_t", metadata !"rsa_t", metadata !"rsa_t", metadata !"rsa_t"}
!44 = metadata !{metadata !"kernel_arg_type_qual", metadata !"", metadata !"", metadata !"", metadata !"", metadata !"", metadata !""}
!45 = metadata !{metadata !"kernel_arg_name", metadata !"x", metadata !"p", metadata !"q", metadata !"dp", metadata !"dq", metadata !"qinv"}
!46 = metadata !{null, metadata !11, metadata !12, metadata !47, metadata !14, metadata !48, metadata !6}
!47 = metadata !{metadata !"kernel_arg_type", metadata !"uint"}
!48 = metadata !{metadata !"kernel_arg_name", metadata !"val"}
!49 = metadata !{null, metadata !50, metadata !51, metadata !52, metadata !53, metadata !54, metadata !6}
!50 = metadata !{metadata !"kernel_arg_addr_space"}
!51 = metadata !{metadata !"kernel_arg_access_qual"}
!52 = metadata !{metadata !"kernel_arg_type"}
!53 = metadata !{metadata !"kernel_arg_type_qual"}
!54 = metadata !{metadata !"kernel_arg_name"}
!55 = metadata !{null, metadata !11, metadata !12, metadata !56, metadata !14, metadata !57, metadata !6}
!56 = metadata !{metadata !"kernel_arg_type", metadata !"const struct ap_uint<32> &"}
!57 = metadata !{metadata !"kernel_arg_name", metadata !"din"}
!58 = metadata !{metadata !59, [1 x i32]* @llvm_global_ctors_0}
!59 = metadata !{metadata !60}
!60 = metadata !{i32 0, i32 31, metadata !61}
!61 = metadata !{metadata !62}
!62 = metadata !{metadata !"llvm.global_ctors.0", metadata !63, metadata !"", i32 0, i32 31}
!63 = metadata !{metadata !64}
!64 = metadata !{i32 0, i32 0, i32 1}
!65 = metadata !{metadata !66}
!66 = metadata !{i32 0, i32 31, metadata !67}
!67 = metadata !{metadata !68}
!68 = metadata !{metadata !"strm_in.V.V", metadata !63, metadata !"uint32", i32 0, i32 31}
!69 = metadata !{metadata !70}
!70 = metadata !{i32 0, i32 31, metadata !71}
!71 = metadata !{metadata !72}
!72 = metadata !{metadata !"strm_out.V.V", metadata !63, metadata !"uint32", i32 0, i32 31}
