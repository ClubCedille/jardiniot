import { createStore, applyMiddleware, compose as composeR } from 'redux';
import { persistStore, persistReducer } from 'redux-persist';
import { connectRouter, routerMiddleware } from 'connected-react-router';
import thunk from 'redux-thunk';
import rootReducer from '../reducers';
import storage from 'redux-persist/lib/storage';
import autoMergeLevel2 from 'redux-persist/lib/stateReconciler/autoMergeLevel2';

const persistConfig = {
  key: 'root',
  storage,
  stateReconciler: autoMergeLevel2
};

const persistedReducer = persistReducer(persistConfig, rootReducer);
const compose = window.__REDUX_DEVTOOLS_EXTENSION_COMPOSE__ || composeR;

export const configureStore = (history) => {
  const routeMiddleware = routerMiddleware(history);
  let store = createStore(
    connectRouter(history)(persistedReducer),
    compose(
      applyMiddleware(routeMiddleware),
      applyMiddleware(thunk),
    ),
  );

  let persistor = persistStore(store);
  return { store, persistor };
};
