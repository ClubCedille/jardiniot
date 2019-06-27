/* global google */
import axios from 'axios';
import { store } from '../index';

export const loginUserSuccess = (user) => ({
  type: 'LOGIN_USER_SUCCESS',
  payload: user
});

export const loginUserFailure = (bool) => ({
  type: 'LOGIN_USER_FAILURE',
  payload: bool
});

export const loginUserPending = (bool) => ({
  type: 'LOGIN_USER_PENDING',
  payload: bool
});

export const signupUserSuccess = (user) => ({
  type: 'SIGNUP_USER_SUCCESS',
  payload: user
});

export const logoutUserSuccess = () => ({
  type: 'LOGOUT_USER_SUCCESS',
  payload: ''
});