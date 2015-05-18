import io
import smtplib
import socket
import tarfile

from email import encoders
from email.mime.base import MIMEBase
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText

FLAG = 'STCTF#URTrueSMTPmaster#'

FROM = 'peterpenctf@gmail.com'
TO = 'box@2015.ppctf.net'

MAIL_TEXT = """Hi there,

Oops, unfortunately there is no flag here.

                               /----\\
                       -------/      \\
                      /               \\
                     /                |
   -----------------/                  --------\\
   ----------------------------------------------

What is it?  It's an elephant being eaten by a snake, of course.

"""

README = """Well, you managed to receive the email and extract its attachment

  < Here is your flag: STCTF#URTrueSMTPmaster# >
    ------------------------------------------
           \   ^__^
            \  (oo)\_______
               (__)\       )\/\\
                   ||----w |
                   ||     ||

"""

def create_flag_tarball():
    tarball_io = io.BytesIO()
    with tarfile.open(fileobj=tarball_io, mode='w:gz') as tarball:
        tar_info = tarfile.TarInfo(name='README')
        tar_info.size = len(README)
        tarball.addfile(tar_info, fileobj=io.BytesIO(README.encode()))
    return tarball_io.getvalue()


def create_message():
    msg = MIMEMultipart()
    msg['From'] = FROM
    msg['To'] = TO
    msg['Subject'] = "StepCTF 2015 - message from another universe"

    attachment = MIMEBase('application/x-tar', 'gzip')
    attachment.set_payload(create_flag_tarball())
    attachment.add_header('Content-Disposition', 'attachment',
                          filename='nothing.tar.gz')
    encoders.encode_base64(attachment)
    msg.attach(MIMEText(MAIL_TEXT))
    msg.attach(attachment)
    return msg


def send_message(server):
    msg = create_message()
    s = smtplib.SMTP(server, timeout=20)
    s.sendmail(FROM, [TO], msg.as_string())
    s.quit()


def test_connection(s):
    assert s.run('true').succeeded, "Could not connect to server"


def test_send_email(s):
    try:
        send_message(s.ip)
    except socket.error:
        assert False, "Failed to connect to SMTP server"
    except:
        assert False, "Failed to send email"


def test_flag_exists(s):
    cmd = 'test -f /home/box/flag.txt'
    assert s.run(cmd).succeeded, "flag.txt not found"


def test_flag_content(s):
    flag_content = s.run('cat /home/box/flag.txt')
    assert flag_content == FLAG, "Incorrect flag in flag.txt"
