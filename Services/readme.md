# PiHome Systemd Services

### Installation directories
- /etc/systemd/system
- /lib/systemd/system **default**
- /run/systemd/system


### Start, Stop & Enable
```bash
sudo systemctl start `service_name`
sudo systemctl stop `service_name`
sudo systemctl enable `service_name`
```

### Create link to .service files

```bash
sudo ln -s ~/PiHome/Services/pihome_nodejs.service pihome_nodejs.service
sudo ln -s ~/PiHome/Services/pihome_cpp.service pihome_cpp.service
```
