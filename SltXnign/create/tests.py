import requests


def test_connection(s):
    assert s.run('true').succeeded, "Could not connect to the server"

def test_nginx_running(s):
    res = s.run('ps -ef | grep [n]ginx')
    assert len(res.split('\n')) > 1, 'No running nginx process found'
    
def test_tls(s):
    try:
        res = requests.get('https://' + s.ip, verify=False)
    except Exception:
        assert False, 'Cannot connect to the HTTPS port'
    assert res.status_code == 200, 'Invalid status code' 
    
    result = s.run('wget https://2015.step.ctf')
    assert result.succeeded, 'Cannot establish a secure connection. Invalid certificate?'
    
def test_content(s):
    try:
        content = requests.get('https://' + s.ip, verify=False).text
    except Exception:
        assert False, 'Cannot connect to the HTTPS port'
    uname_str = s.run('uname -a')
    assert uname_str in content, 'No "uname" output found in the response'
    


