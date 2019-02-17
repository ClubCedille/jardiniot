import React from 'react';
import ReactDOM from 'react-dom';
import App from './App';
import registerServiceWorker from './registerServiceWorker';
import createHistory from 'history/createBrowserHistory';
import { Provider } from 'react-redux';
import { configureStore } from './store';
import { ConnectedRouter } from 'connected-react-router';
import { BrowserRouter } from 'react-router-dom';
import { PersistGate } from 'redux-persist/integration/react';

export const history = createHistory();
export const { store, persistor } = configureStore(history);

ReactDOM.render(
  <Provider store={store}>
    <PersistGate loading={null} persistor={persistor}>
      <ConnectedRouter history={history}>
        <BrowserRouter>
          <App/>
        </BrowserRouter>
      </ConnectedRouter>
    </PersistGate>
  </Provider>,
  document.getElementById('root')
);

registerServiceWorker();