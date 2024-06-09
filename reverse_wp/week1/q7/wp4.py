import angr
import claripy
def main():
    p = angr.Project("./exes/Ee2ICjkC.exe",main_opts={'base_addr': 0x140000000}, auto_load_libs=False)
    flag = claripy.BVS('flag', 8*35)
    state = p.factory.blank_state(addr=0x14000157F)
    buf = state.regs.rbp-0x50
    state.memory.store(buf, flag)
    for i in range(35):
        state.add_constraints(flag.get_byte(i) >= 0x20)
        state.add_constraints(flag.get_byte(i) <= 0x7e)
    sm = p.factory.simulation_manager(state)
    sm.explore(find=0x140001908, avoid=0x1400018E8)
    found = sm.found[0]
    solution = found.solver.eval(flag, cast_to=bytes)
    print(solution)

if __name__ == '__main__':
    main()

        
# WARNING  | 2024-04-11 20:56:44,237 | angr.storage.memory_mixins.default_filler_mixin | The program is accessing register with an unspecified value. This could indicate unwanted behavior.
# WARNING  | 2024-04-11 20:56:44,237 | angr.storage.memory_mixins.default_filler_mixin | angr will cope with this by generating an unconstrained symbolic variable and continuing. You can resolve this by:
# WARNING  | 2024-04-11 20:56:44,237 | angr.storage.memory_mixins.default_filler_mixin | 1) setting a value to the initial state
# WARNING  | 2024-04-11 20:56:44,237 | angr.storage.memory_mixins.default_filler_mixin | 2) adding the state option ZERO_FILL_UNCONSTRAINED_{MEMORY,REGISTERS}, to make unknown regions hold null
# WARNING  | 2024-04-11 20:56:44,237 | angr.storage.memory_mixins.default_filler_mixin | 3) adding the state option SYMBOL_FILL_UNCONSTRAINED_{MEMORY,REGISTERS}, to suppress these messages.
# WARNING  | 2024-04-11 20:56:44,237 | angr.storage.memory_mixins.default_filler_mixin | Filling register rbp with 8 unconstrained bytes referenced from 0x14000157f (offset 0x157f in Ee2ICjkC.exe (0x14000157f))
# b'flag{calculation_is_ready_5a36355a}'
    