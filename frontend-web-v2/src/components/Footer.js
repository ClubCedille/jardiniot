import React, { Component } from 'react';

const Footer = (props) => {
	return (
		<div className="footer">
			<p>&copy; F O O T E R - {new Date().getFullYear()} <strong>Jardiniot</strong> - Cédille</p>
		</div>
	);
};

export default Footer;