FLAG_CONTENT = "# this is the first line of flag.txt\r\nSTCTF#WellDumped#\r\n# this is the last line of flag.txt"


def test_connection(s):
    assert s.run('true').succeeded, "Could not connect to server"


def test_flag_exists(s):
    cmd = 'test -f /home/box/flag.txt'
    assert s.run(cmd).succeeded, "flag.txt not found"


def test_flag_content(s):
    flag_content = s.run('cat /home/box/flag.txt')
    assert flag_content == FLAG_CONTENT, "Incorrect flag.txt content"
