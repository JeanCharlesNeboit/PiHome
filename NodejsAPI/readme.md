# Nodejs

### Install
```bash
npm install
```

- add `db_config.json` file in `./database`
  ```json
  {
    "host" : "IP",
    "user" : "USERNAME",
    "password" : "PASSWORD",
    "database" : "DATABASE"
  }
  ```
- add `config.json` file
  ```json
  {
    "secretKey": "SECRETKEY",
    "allowIPs": ["IP"]
  }
  ```
- add `certificates.json` file
  ```json
  {
    "key": "private key path",
    "cert": "cert path",
    "ca": "ca path"
  }
  ```

### Start
```bash
npm start
```
