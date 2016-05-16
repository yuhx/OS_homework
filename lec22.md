#lec22 Report

在读操作的最底层函数disk0_read_blks_nolock（读取连续块）中增加print_stackframe，我们不难得到如下输出：

ebp:0xc03699f8 eip:0xc0100bd2 args:0xc0152fe0 0x00000100 0xc0369a38 0x00000000 
    kern/debug/kdebug.c:350: print_stackframe+21
ebp:0xc0369a38 eip:0xc0110ccc args:0x0000005a 0x00000001 0x04000000 0xc0367008 
    kern/fs/devs/dev_disk0.c:42: disk0_read_blks_nolock+10
ebp:0xc0369a88 eip:0xc0110f2b args:0xc03562b8 0xc0369aac 0x00000000 0x0005a000 
    kern/fs/devs/dev_disk0.c:98: disk0_io+334
ebp:0xc0369ac8 eip:0xc01146a9 args:0xc0356340 0xc0364000 0x0000005a 0x00000000 
    kern/fs/sfs/sfs_io.c:23: sfs_rwblock_nolock+137
ebp:0xc0369b08 eip:0xc01147fc args:0xc0356340 0xc0395000 0x00000020 0x0000005a 
    kern/fs/sfs/sfs_io.c:89: sfs_rbuf+126
ebp:0xc0369b68 eip:0xc01134e4 args:0xc0356340 0xc0356f18 0xc0395000 0x00000074 
    kern/fs/sfs/sfs_inode.c:607: sfs_io_nolock+437
ebp:0xc0369bb8 eip:0xc011371a args:0xc0356f18 0xc0369bfc 0x00000000 0x00000001 
    kern/fs/sfs/sfs_inode.c:658: sfs_io+210
ebp:0xc0369bd8 eip:0xc0113766 args:0xc0356f18 0xc0369bfc 0x00000020 0x00000074 
    kern/fs/sfs/sfs_inode.c:670: sfs_read+31
ebp:0xc0369c28 eip:0xc010aafd args:0x00000000 0xc0395000 0x00000020 0xc0369c4c 
    kern/fs/file.c:226: file_read+238
ebp:0xc0369c68 eip:0xc010b7af args:0x00000000 0xc0369ccc 0x00000020 0x00000004 
    kern/fs/sysfile.c:80: sysfile_read+176
ebp:0xc0369c98 eip:0xc010ce6a args:0x00000000 0xc0369ccc 0x00000020 0x00000074 
    kern/process/proc.c:581: load_icode_read+70
ebp:0xc0369d88 eip:0xc010cfb4 args:0x00000000 0x00000001 0xc0369da8 0xc0369fdc 
    kern/process/proc.c:646: load_icode+296
ebp:0xc0369e78 eip:0xc010d98f args:0xc01183f0 0x00000001 0xc0369fdc 0x037a08ac 
    kern/process/proc.c:855: do_execve+444
ebp:0xc0369ea8 eip:0xc010ebea args:0xc0369ed4 0x00000001 0x00000000 0x00000000 
    kern/syscall/syscall.c:39: sys_exec+60
ebp:0xc0369ef8 eip:0xc010eeda args:0xc0114d17 0x0000000a 0xc0369f80 0xffff6ad9 
    kern/syscall/syscall.c:199: syscall+117
ebp:0xc0369f28 eip:0xc01029b3 args:0xc0369f64 0xfffffffa 0x0000000a 0x00000002 
    kern/trap/trap.c:217: trap_dispatch+299
ebp:0xc0369f58 eip:0xc0102ac1 args:0xc0369f64 0x00000000 0x00000000 0xc0369fbc 
    kern/trap/trap.c:298: trap+74
ebp:0xc0369fbc eip:0xc0102b16 args:0xc01183f0 0xc0369fdc 0xc01183f0 0x00000000 
    kern/trap/trapentry.S:24: <unknown>+0
ebp:0xc0369fec eip:0xc010dcb6 args:0x00000000 0x00000000 0x00000010 0xc0356458 
    kern/process/proc.c:992: user_main+70

可以看到如下流程：
从系统调用开始 syscall -> sys_exec -> do_execve -> load_icode -> load_icode_read -> sysfile_read -> file_read -> sfs_read -> sfs_io -> sfs_io_nolock -> sfs_rbuf -> sfs_rwblock_nolock -> disk0_io -> disk0_read_blks_nolock


