
main.o:     file format elf32-i386


Disassembly of section .init:

0804828c <_init>:
 804828c:	53                   	push   ebx
 804828d:	83 ec 08             	sub    esp,0x8
 8048290:	e8 9b 00 00 00       	call   8048330 <__x86.get_pc_thunk.bx>
 8048295:	81 c3 6b 1d 00 00    	add    ebx,0x1d6b
 804829b:	8b 83 fc ff ff ff    	mov    eax,DWORD PTR [ebx-0x4]
 80482a1:	85 c0                	test   eax,eax
 80482a3:	74 05                	je     80482aa <_init+0x1e>
 80482a5:	e8 26 00 00 00       	call   80482d0 <__gmon_start__@plt>
 80482aa:	83 c4 08             	add    esp,0x8
 80482ad:	5b                   	pop    ebx
 80482ae:	c3                   	ret    

Disassembly of section .plt:

080482b0 <.plt>:
 80482b0:	ff 35 04 a0 04 08    	push   DWORD PTR ds:0x804a004
 80482b6:	ff 25 08 a0 04 08    	jmp    DWORD PTR ds:0x804a008
 80482bc:	00 00                	add    BYTE PTR [eax],al
	...

080482c0 <__libc_start_main@plt>:
 80482c0:	ff 25 0c a0 04 08    	jmp    DWORD PTR ds:0x804a00c
 80482c6:	68 00 00 00 00       	push   0x0
 80482cb:	e9 e0 ff ff ff       	jmp    80482b0 <.plt>

Disassembly of section .plt.got:

080482d0 <__gmon_start__@plt>:
 80482d0:	ff 25 fc 9f 04 08    	jmp    DWORD PTR ds:0x8049ffc
 80482d6:	66 90                	xchg   ax,ax

Disassembly of section .text:

080482e0 <_start>:
 80482e0:	31 ed                	xor    ebp,ebp
 80482e2:	5e                   	pop    esi
 80482e3:	89 e1                	mov    ecx,esp
 80482e5:	83 e4 f0             	and    esp,0xfffffff0
 80482e8:	50                   	push   eax
 80482e9:	54                   	push   esp
 80482ea:	52                   	push   edx
 80482eb:	e8 23 00 00 00       	call   8048313 <_start+0x33>
 80482f0:	81 c3 10 1d 00 00    	add    ebx,0x1d10
 80482f6:	8d 83 80 e4 ff ff    	lea    eax,[ebx-0x1b80]
 80482fc:	50                   	push   eax
 80482fd:	8d 83 20 e4 ff ff    	lea    eax,[ebx-0x1be0]
 8048303:	50                   	push   eax
 8048304:	51                   	push   ecx
 8048305:	56                   	push   esi
 8048306:	c7 c0 f6 83 04 08    	mov    eax,0x80483f6
 804830c:	50                   	push   eax
 804830d:	e8 ae ff ff ff       	call   80482c0 <__libc_start_main@plt>
 8048312:	f4                   	hlt    
 8048313:	8b 1c 24             	mov    ebx,DWORD PTR [esp]
 8048316:	c3                   	ret    
 8048317:	66 90                	xchg   ax,ax
 8048319:	66 90                	xchg   ax,ax
 804831b:	66 90                	xchg   ax,ax
 804831d:	66 90                	xchg   ax,ax
 804831f:	90                   	nop

08048320 <_dl_relocate_static_pie>:
 8048320:	f3 c3                	repz ret 
 8048322:	66 90                	xchg   ax,ax
 8048324:	66 90                	xchg   ax,ax
 8048326:	66 90                	xchg   ax,ax
 8048328:	66 90                	xchg   ax,ax
 804832a:	66 90                	xchg   ax,ax
 804832c:	66 90                	xchg   ax,ax
 804832e:	66 90                	xchg   ax,ax

08048330 <__x86.get_pc_thunk.bx>:
 8048330:	8b 1c 24             	mov    ebx,DWORD PTR [esp]
 8048333:	c3                   	ret    
 8048334:	66 90                	xchg   ax,ax
 8048336:	66 90                	xchg   ax,ax
 8048338:	66 90                	xchg   ax,ax
 804833a:	66 90                	xchg   ax,ax
 804833c:	66 90                	xchg   ax,ax
 804833e:	66 90                	xchg   ax,ax

08048340 <deregister_tm_clones>:
 8048340:	b8 18 a0 04 08       	mov    eax,0x804a018
 8048345:	3d 18 a0 04 08       	cmp    eax,0x804a018
 804834a:	74 24                	je     8048370 <deregister_tm_clones+0x30>
 804834c:	b8 00 00 00 00       	mov    eax,0x0
 8048351:	85 c0                	test   eax,eax
 8048353:	74 1b                	je     8048370 <deregister_tm_clones+0x30>
 8048355:	55                   	push   ebp
 8048356:	89 e5                	mov    ebp,esp
 8048358:	83 ec 14             	sub    esp,0x14
 804835b:	68 18 a0 04 08       	push   0x804a018
 8048360:	ff d0                	call   eax
 8048362:	83 c4 10             	add    esp,0x10
 8048365:	c9                   	leave  
 8048366:	c3                   	ret    
 8048367:	89 f6                	mov    esi,esi
 8048369:	8d bc 27 00 00 00 00 	lea    edi,[edi+eiz*1+0x0]
 8048370:	f3 c3                	repz ret 
 8048372:	8d b4 26 00 00 00 00 	lea    esi,[esi+eiz*1+0x0]
 8048379:	8d bc 27 00 00 00 00 	lea    edi,[edi+eiz*1+0x0]

08048380 <register_tm_clones>:
 8048380:	b8 18 a0 04 08       	mov    eax,0x804a018
 8048385:	2d 18 a0 04 08       	sub    eax,0x804a018
 804838a:	c1 f8 02             	sar    eax,0x2
 804838d:	89 c2                	mov    edx,eax
 804838f:	c1 ea 1f             	shr    edx,0x1f
 8048392:	01 d0                	add    eax,edx
 8048394:	d1 f8                	sar    eax,1
 8048396:	74 20                	je     80483b8 <register_tm_clones+0x38>
 8048398:	ba 00 00 00 00       	mov    edx,0x0
 804839d:	85 d2                	test   edx,edx
 804839f:	74 17                	je     80483b8 <register_tm_clones+0x38>
 80483a1:	55                   	push   ebp
 80483a2:	89 e5                	mov    ebp,esp
 80483a4:	83 ec 10             	sub    esp,0x10
 80483a7:	50                   	push   eax
 80483a8:	68 18 a0 04 08       	push   0x804a018
 80483ad:	ff d2                	call   edx
 80483af:	83 c4 10             	add    esp,0x10
 80483b2:	c9                   	leave  
 80483b3:	c3                   	ret    
 80483b4:	8d 74 26 00          	lea    esi,[esi+eiz*1+0x0]
 80483b8:	f3 c3                	repz ret 
 80483ba:	8d b6 00 00 00 00    	lea    esi,[esi+0x0]

080483c0 <__do_global_dtors_aux>:
 80483c0:	80 3d 20 a0 04 08 00 	cmp    BYTE PTR ds:0x804a020,0x0
 80483c7:	75 17                	jne    80483e0 <__do_global_dtors_aux+0x20>
 80483c9:	55                   	push   ebp
 80483ca:	89 e5                	mov    ebp,esp
 80483cc:	83 ec 08             	sub    esp,0x8
 80483cf:	e8 6c ff ff ff       	call   8048340 <deregister_tm_clones>
 80483d4:	c6 05 20 a0 04 08 01 	mov    BYTE PTR ds:0x804a020,0x1
 80483db:	c9                   	leave  
 80483dc:	c3                   	ret    
 80483dd:	8d 76 00             	lea    esi,[esi+0x0]
 80483e0:	f3 c3                	repz ret 
 80483e2:	8d b4 26 00 00 00 00 	lea    esi,[esi+eiz*1+0x0]
 80483e9:	8d bc 27 00 00 00 00 	lea    edi,[edi+eiz*1+0x0]

080483f0 <frame_dummy>:
 80483f0:	55                   	push   ebp
 80483f1:	89 e5                	mov    ebp,esp
 80483f3:	5d                   	pop    ebp
 80483f4:	eb 8a                	jmp    8048380 <register_tm_clones>

080483f6 <main>:
 80483f6:	55                   	push   ebp
 80483f7:	89 e5                	mov    ebp,esp
 80483f9:	57                   	push   edi
 80483fa:	56                   	push   esi
 80483fb:	53                   	push   ebx
 80483fc:	ba 40 a0 04 08       	mov    edx,0x804a040
 8048401:	bb c0 84 04 08       	mov    ebx,0x80484c0
 8048406:	b8 1a 00 00 00       	mov    eax,0x1a
 804840b:	89 d7                	mov    edi,edx
 804840d:	89 de                	mov    esi,ebx
 804840f:	89 c1                	mov    ecx,eax
 8048411:	f3 a5                	rep movs DWORD PTR es:[edi],DWORD PTR ds:[esi]
 8048413:	b8 00 00 00 00       	mov    eax,0x0
 8048418:	5b                   	pop    ebx
 8048419:	5e                   	pop    esi
 804841a:	5f                   	pop    edi
 804841b:	5d                   	pop    ebp
 804841c:	c3                   	ret    
 804841d:	66 90                	xchg   ax,ax
 804841f:	90                   	nop

08048420 <__libc_csu_init>:
 8048420:	55                   	push   ebp
 8048421:	57                   	push   edi
 8048422:	56                   	push   esi
 8048423:	53                   	push   ebx
 8048424:	e8 07 ff ff ff       	call   8048330 <__x86.get_pc_thunk.bx>
 8048429:	81 c3 d7 1b 00 00    	add    ebx,0x1bd7
 804842f:	83 ec 0c             	sub    esp,0xc
 8048432:	8b 6c 24 28          	mov    ebp,DWORD PTR [esp+0x28]
 8048436:	8d b3 10 ff ff ff    	lea    esi,[ebx-0xf0]
 804843c:	e8 4b fe ff ff       	call   804828c <_init>
 8048441:	8d 83 0c ff ff ff    	lea    eax,[ebx-0xf4]
 8048447:	29 c6                	sub    esi,eax
 8048449:	c1 fe 02             	sar    esi,0x2
 804844c:	85 f6                	test   esi,esi
 804844e:	74 25                	je     8048475 <__libc_csu_init+0x55>
 8048450:	31 ff                	xor    edi,edi
 8048452:	8d b6 00 00 00 00    	lea    esi,[esi+0x0]
 8048458:	83 ec 04             	sub    esp,0x4
 804845b:	55                   	push   ebp
 804845c:	ff 74 24 2c          	push   DWORD PTR [esp+0x2c]
 8048460:	ff 74 24 2c          	push   DWORD PTR [esp+0x2c]
 8048464:	ff 94 bb 0c ff ff ff 	call   DWORD PTR [ebx+edi*4-0xf4]
 804846b:	83 c7 01             	add    edi,0x1
 804846e:	83 c4 10             	add    esp,0x10
 8048471:	39 fe                	cmp    esi,edi
 8048473:	75 e3                	jne    8048458 <__libc_csu_init+0x38>
 8048475:	83 c4 0c             	add    esp,0xc
 8048478:	5b                   	pop    ebx
 8048479:	5e                   	pop    esi
 804847a:	5f                   	pop    edi
 804847b:	5d                   	pop    ebp
 804847c:	c3                   	ret    
 804847d:	8d 76 00             	lea    esi,[esi+0x0]

08048480 <__libc_csu_fini>:
 8048480:	f3 c3                	repz ret 

Disassembly of section .fini:

08048484 <_fini>:
 8048484:	53                   	push   ebx
 8048485:	83 ec 08             	sub    esp,0x8
 8048488:	e8 a3 fe ff ff       	call   8048330 <__x86.get_pc_thunk.bx>
 804848d:	81 c3 73 1b 00 00    	add    ebx,0x1b73
 8048493:	83 c4 08             	add    esp,0x8
 8048496:	5b                   	pop    ebx
 8048497:	c3                   	ret    
