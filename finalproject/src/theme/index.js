  
import { createTheme } from '@material-ui/core/styles';
import { colors } from '@material-ui/core';

// Create a theme instance.
const theme = createTheme({
  palette: {
    background: {
      default: colors.common.white,
      dark: '#f4f6f8',
      paper: colors.common.white,
    },
    primary: {
      main: '#f44336',
    },
    secondary: {
      main: '#3ea6ff',
    },
    text: {
      primary: colors.blueGrey[900],
      secondary: colors.blueGrey[600],
    }
}});

export default theme;