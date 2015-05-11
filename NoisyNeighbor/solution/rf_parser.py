#!/usr/bin/env python3
import struct
import sys
import wave


FILENAME = sys.argv[1]

TRI_STATE_SEQUENCE_LENGTH = 12
IS_SYNC_BIT_LOW = lambda inter: inter[0] == 0 and 450 < inter[1] < 500
IS_LOW = lambda inter: inter[0] == 0 and 15 < inter[1] < 30
IS_HIGH = lambda inter: inter[0] == 1 and 15 < inter[1] < 30
IS_3LOW = lambda inter: inter[0] == 0 and 45 < inter[1] < 55
IS_3HIGH = lambda inter: inter[0] == 1 and 45 < inter[1] < 55


def read_pulses_sequence(intervals, index, pulses, bit):
    if all(is_pulse(inter) for is_pulse, inter in
           zip(pulses, intervals[index:index + len(pulses)])):
        return bit, index + len(pulses)
    return None, None


def read_tri_state_0(intervals, index):
    pulses = [IS_HIGH, IS_3LOW, IS_HIGH, IS_3LOW]
    return read_pulses_sequence(intervals, index, pulses, '0')


def read_tri_state_1(intervals, index):
    pulses = [IS_3HIGH, IS_LOW, IS_3HIGH, IS_LOW]
    return read_pulses_sequence(intervals, index, pulses, '1')


def read_tri_state_F(intervals, index):
    pulses = [IS_HIGH, IS_3LOW, IS_3HIGH, IS_LOW]
    return read_pulses_sequence(intervals, index, pulses, 'F')


def read_tri_state(intervals, index):
    read_funcs = [read_tri_state_0, read_tri_state_1, read_tri_state_F]
    for read_func in read_funcs:
        bit, new_index = read_func(intervals, index)
        if bit:
            return bit, new_index
    return None, None


def read_tri_state_sequence(intervals, index):
    sequence = []
    for i in range(TRI_STATE_SEQUENCE_LENGTH):
        tri_state, index = read_tri_state(intervals, index)
        if not tri_state:
            return None, None
        sequence.append(tri_state)
    return ''.join(sequence), index


def read_sync_bit(intervals, index):
    if IS_HIGH(intervals[index]) and IS_SYNC_BIT_LOW(intervals[index + 1]):
        return True, index + 2
    return None, None


wf = wave.open(FILENAME)

signal_intervals = []
signal = 0
signal_length = 0
for i in range(wf.getnframes()):
    frame_data = wf.readframes(1)
    frame = struct.unpack("<h", frame_data)[0]
    new_signal = 1 if frame > 0 else 0
    if new_signal == signal:
        signal_length += 1
    else:
        signal_intervals.append((signal, signal_length))
        signal = new_signal
        signal_length = 1


tri_state_sequences = []
index = 0
while index < len(signal_intervals) - 1:
    is_sync_bit, new_index = read_sync_bit(signal_intervals, index)
    if not is_sync_bit:
        index += 1
        continue
    index = new_index
    #print("# Sync bit:", index)

    tri_state_seq, new_index = read_tri_state_sequence(signal_intervals, index)
    if tri_state_seq:
        tri_state_sequences.append(tri_state_seq)
        index = new_index
        #print("# Read tri-state:", tri_state_seq)
        if tri_state_seq.startswith('FFFFF'):
            sys.stdout.write(chr(int(tri_state_seq[5:], 2)))
