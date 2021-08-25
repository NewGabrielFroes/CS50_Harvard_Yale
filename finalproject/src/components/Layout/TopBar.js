import { makeStyles } from '@material-ui/core/styles';
import AppBar from '@material-ui/core/AppBar';
import Toolbar from '@material-ui/core/Toolbar';
import Box from '@material-ui/core/Box'
import MenuIcon from '@material-ui/icons/Menu'

const useStyles = makeStyles((theme) => ({
  root: {
    boxShadow: 'none',
    zIndex: theme.zIndex.drawer + 1,
    backgroundColor: theme.palette.background.default,
  },
  toolbar: {
    minHeight: 56,
    display: 'flex',
    alignItems: 'center',
    justifyContent: 'space-between',
  },
  logo: {
    cursor: 'pointer',
    height: 18,
    marginLeft: theme.spacing(3),
  },
  search: {
    padding: '2px 4px',
    display: 'flex',
    alignItems: 'center',
    height: 35,
    width: 700,
  },
  input: {
    flex: 1,
  }
}))

function TopBar(){
  const classes = useStyles()
  return (
    <AppBar className={classes.root} color="default">
      <Toolbar classname={classes.toolbar}>
        <Box display="flex" alignItems="center">
          <MenuIcon />
          <img src="/new-youtube-logo.svg" alt="logo" className={classes.logo}/>
        </Box>
        <Box></Box>
        <Box></Box>
      </Toolbar>
    </AppBar>
  )
}

export default TopBar