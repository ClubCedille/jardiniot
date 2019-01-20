/**
 * Adaptateur d'axios utilisant l'URL de base de l'api
 * Author: Roch D'Amour
 */

import axios from 'axios';

export default axios.create({
  baseURL: 'http://localhost:5000',
  timeout: 10000,
  withCredentials: false,
});